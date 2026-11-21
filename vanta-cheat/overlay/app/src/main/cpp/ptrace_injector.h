// ptrace_injector.h — внедряет указанную .so в чужой процесс через ptrace.
// требования: процесс чита должен быть root (или иметь CAP_SYS_PTRACE) и ptrace_scope разрешён.
#pragma once

#include <sys/types.h>
#include <string>

namespace vanta {

struct InjectResult {
    bool     success;
    int      error_code;
    uintptr_t remote_handle;    // возвращённый dlopen handle в чужом процессе
    uintptr_t remote_sym;       // адрес вызванной entry-функции
    std::string message;
};

// so_path — абсолютный путь к .so в файловой системе процесса чита.
// перед вызовом мы копируем его в /data/local/tmp/ с правами 0644, чтобы игра смогла mmap-нуть.
// entry_name — имя функции в этой .so, которая будет вызвана (void)()
InjectResult inject_so(pid_t pid, const char* so_path_in_target_fs, const char* entry_name);

} // namespace vanta
