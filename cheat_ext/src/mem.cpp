#include "mem.hpp"

#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/uio.h>

#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <stdexcept>

namespace ext {

pid_t find_pid(const char* package) {
    DIR* d = opendir("/proc");
    if (!d) return 0;
    pid_t found = 0;
    size_t want = std::strlen(package);
    char buf[256];
    while (dirent* e = readdir(d)) {
        char* end = nullptr;
        long n = std::strtol(e->d_name, &end, 10);
        if (*end || n <= 0) continue;
        std::snprintf(buf, sizeof(buf), "/proc/%ld/cmdline", n);
        int fd = open(buf, O_RDONLY | O_CLOEXEC);
        if (fd < 0) continue;
        ssize_t r = read(fd, buf, sizeof(buf) - 1);
        close(fd);
        if (r <= 0) continue;
        buf[r] = 0;
        // cmdline is NUL-separated argv; first field is the process name.
        if (std::strncmp(buf, package, want) == 0 && (buf[want] == 0 || buf[want] == ':')) {
            found = static_cast<pid_t>(n);
            break;
        }
    }
    closedir(d);
    return found;
}

std::vector<Mapping> read_maps(pid_t pid) {
    char path[64];
    std::snprintf(path, sizeof(path), "/proc/%d/maps", pid);
    std::ifstream f(path);
    if (!f) throw std::runtime_error(std::string("open ") + path);
    std::vector<Mapping> out;
    std::string line;
    while (std::getline(f, line)) {
        unsigned long a, b, o;
        char perms[8];
        int used = 0;
        if (std::sscanf(line.c_str(), "%lx-%lx %7s %lx %*s %*s %n",
                        &a, &b, perms, &o, &used) != 4) continue;
        int pbits = 0;
        if (perms[0] == 'r') pbits |= 1;
        if (perms[1] == 'w') pbits |= 2;
        if (perms[2] == 'x') pbits |= 4;
        std::string p = line.substr(used);
        while (!p.empty() && p.front() == ' ') p.erase(0, 1);
        out.push_back({a, b, o, pbits, std::move(p)});
    }
    return out;
}

uintptr_t module_base(pid_t pid, const char* module) {
    auto maps = read_maps(pid);
    for (const auto& m : maps) {
        // Match the basename to avoid picking the wrong namespace copy.
        const char* slash = std::strrchr(m.path.c_str(), '/');
        const char* base = slash ? slash + 1 : m.path.c_str();
        if (std::strcmp(base, module) == 0 && m.offset == 0) return m.start;
    }
    return 0;
}

// Raw syscall wrappers. We use SYS_process_vm_readv / SYS_process_vm_writev so
// a libc-level PLT hook by the target process's anti-cheat on the glibc
// wrappers does not intercept us. (That anti-cheat lives in the game's
// address space anyway, but defence in depth is cheap here.)
static ssize_t raw_vm_readv(pid_t pid, const iovec* li, unsigned long ln,
                            const iovec* ri, unsigned long rn, unsigned long flags) {
    return syscall(SYS_process_vm_readv, pid, li, ln, ri, rn, flags);
}
static ssize_t raw_vm_writev(pid_t pid, const iovec* li, unsigned long ln,
                             const iovec* ri, unsigned long rn, unsigned long flags) {
    return syscall(SYS_process_vm_writev, pid, li, ln, ri, rn, flags);
}

bool read_bytes(pid_t pid, uintptr_t addr, void* out, size_t len) {
    iovec li{out, len};
    iovec ri{reinterpret_cast<void*>(addr), len};
    size_t left = len;
    while (left) {
        iovec lp{static_cast<char*>(li.iov_base) + (len - left), left};
        iovec rp{reinterpret_cast<char*>(ri.iov_base) + (len - left), left};
        ssize_t n = raw_vm_readv(pid, &lp, 1, &rp, 1, 0);
        if (n <= 0) return false;
        left -= static_cast<size_t>(n);
    }
    return true;
}

bool write_bytes(pid_t pid, uintptr_t addr, const void* in, size_t len) {
    iovec li{const_cast<void*>(in), len};
    iovec ri{reinterpret_cast<void*>(addr), len};
    size_t left = len;
    while (left) {
        iovec lp{static_cast<char*>(li.iov_base) + (len - left), left};
        iovec rp{reinterpret_cast<char*>(ri.iov_base) + (len - left), left};
        ssize_t n = raw_vm_writev(pid, &lp, 1, &rp, 1, 0);
        if (n <= 0) return false;
        left -= static_cast<size_t>(n);
    }
    return true;
}

uintptr_t chain(pid_t pid, uintptr_t base, std::initializer_list<ptrdiff_t> offsets) {
    uintptr_t cursor = base;
    for (ptrdiff_t off : offsets) {
        uintptr_t next = 0;
        if (!read_bytes(pid, cursor, &next, sizeof(next))) return 0;
        cursor = next + off;
    }
    return cursor;
}

std::string read_il2cpp_string(pid_t pid, uintptr_t string_object) {
    if (!string_object) return {};
    // IL2CPP System.String layout: Object header (0x10) + length (int32, 0x10) + chars (UTF-16, 0x14).
    int32_t length = 0;
    if (!read_bytes(pid, string_object + 0x10, &length, sizeof(length))) return {};
    if (length <= 0 || length > 4096) return {};
    std::vector<uint16_t> chars(static_cast<size_t>(length));
    if (!read_bytes(pid, string_object + 0x14, chars.data(), chars.size() * sizeof(uint16_t))) return {};
    std::string out;
    out.reserve(static_cast<size_t>(length));
    for (int i = 0; i < length; i++) {
        uint32_t cp = chars[i];
        if (cp >= 0xd800 && cp <= 0xdbff && i + 1 < length &&
            chars[i + 1] >= 0xdc00 && chars[i + 1] <= 0xdfff) {
            cp = 0x10000 + ((cp - 0xd800) << 10) + (chars[++i] - 0xdc00);
        }
        if (cp < 0x80) out.push_back(static_cast<char>(cp));
        else if (cp < 0x800) {
            out.push_back(static_cast<char>(0xc0 | (cp >> 6)));
            out.push_back(static_cast<char>(0x80 | (cp & 0x3f)));
        } else if (cp < 0x10000) {
            out.push_back(static_cast<char>(0xe0 | (cp >> 12)));
            out.push_back(static_cast<char>(0x80 | ((cp >> 6) & 0x3f)));
            out.push_back(static_cast<char>(0x80 | (cp & 0x3f)));
        } else {
            out.push_back(static_cast<char>(0xf0 | (cp >> 18)));
            out.push_back(static_cast<char>(0x80 | ((cp >> 12) & 0x3f)));
            out.push_back(static_cast<char>(0x80 | ((cp >> 6) & 0x3f)));
            out.push_back(static_cast<char>(0x80 | (cp & 0x3f)));
        }
    }
    return out;
}

} // namespace ext
