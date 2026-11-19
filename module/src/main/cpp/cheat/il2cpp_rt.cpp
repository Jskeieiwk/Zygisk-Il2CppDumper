#include "il2cpp_rt.h"

#include <cinttypes>
#include <cstdio>
#include <cstring>
#include <dlfcn.h>

#include "ms_log.h"
#include "xdl.h"

namespace ms::il2cpp {

Api api{};

namespace {

struct Range {
    uintptr_t begin;
    uintptr_t end;
};

constexpr int kMaxRanges = 8;
Range g_text[kMaxRanges];
int g_text_count = 0;

template<class Fn>
bool load_one(void *handle, const char *name, Fn &slot) {
    slot = reinterpret_cast<Fn>(xdl_sym(handle, name, nullptr));
    if (!slot) {
        slot = reinterpret_cast<Fn>(xdl_dsym(handle, name, nullptr));
    }
    if (!slot) {
        MS_LOGE("il2cpp api missing: %s", name);
        return false;
    }
    return true;
}

bool type_name_equals(const void *type, const char *expected) {
    if (!type || !expected) return false;
    char *name = api.type_get_name(type);
    if (!name) return false;
    const bool eq = std::strcmp(name, expected) == 0;
    api.free_mem(name);
    return eq;
}

}  // namespace

bool load_api(void *h) {
    bool ok = true;
    ok &= load_one(h, "il2cpp_is_vm_thread", api.is_vm_thread);
    ok &= load_one(h, "il2cpp_domain_get", api.domain_get);
    ok &= load_one(h, "il2cpp_domain_get_assemblies", api.domain_get_assemblies);
    ok &= load_one(h, "il2cpp_assembly_get_image", api.assembly_get_image);
    ok &= load_one(h, "il2cpp_image_get_name", api.image_get_name);
    ok &= load_one(h, "il2cpp_class_from_name", api.class_from_name);
    ok &= load_one(h, "il2cpp_class_get_methods", api.class_get_methods);
    ok &= load_one(h, "il2cpp_method_get_name", api.method_get_name);
    ok &= load_one(h, "il2cpp_method_get_param_count", api.method_get_param_count);
    ok &= load_one(h, "il2cpp_method_get_param", api.method_get_param);
    ok &= load_one(h, "il2cpp_method_get_flags", api.method_get_flags);
    ok &= load_one(h, "il2cpp_type_get_name", api.type_get_name);
    ok &= load_one(h, "il2cpp_type_get_type", api.type_get_type);
    ok &= load_one(h, "il2cpp_free", api.free_mem);
    ok &= load_one(h, "il2cpp_class_get_field_from_name", api.class_get_field_from_name);
    ok &= load_one(h, "il2cpp_field_get_offset", api.field_get_offset);
    ok &= load_one(h, "il2cpp_field_get_type", api.field_get_type);
    ok &= load_one(h, "il2cpp_field_get_flags", api.field_get_flags);
    ok &= load_one(h, "il2cpp_field_static_get_value", api.field_static_get_value);
    ok &= load_one(h, "il2cpp_field_static_set_value", api.field_static_set_value);
    ok &= load_one(h, "il2cpp_class_get_type", api.class_get_type);
    ok &= load_one(h, "il2cpp_type_get_object", api.type_get_object);
    ok &= load_one(h, "il2cpp_string_new", api.string_new);
    ok &= load_one(h, "il2cpp_array_length", api.array_length);
    ok &= load_one(h, "il2cpp_runtime_class_init", api.runtime_class_init);
    ok &= load_one(h, "il2cpp_thread_attach", api.thread_attach);
    ok &= load_one(h, "il2cpp_thread_detach", api.thread_detach);
    return ok;
}

bool init_module_range(void *any_il2cpp_symbol) {
    Dl_info info{};
    if (!dladdr(any_il2cpp_symbol, &info) || !info.dli_fname) {
        MS_LOGE("dladdr failed for il2cpp symbol");
        return false;
    }
    FILE *maps = std::fopen("/proc/self/maps", "re");
    if (!maps) return false;
    char line[1024];
    g_text_count = 0;
    while (std::fgets(line, sizeof(line), maps) && g_text_count < kMaxRanges) {
        uintptr_t b = 0, e = 0;
        char perms[8] = {};
        if (std::sscanf(line, "%" SCNxPTR "-%" SCNxPTR " %7s", &b, &e, perms) != 3) continue;
        if (perms[2] != 'x') continue;
        if (!std::strstr(line, info.dli_fname)) continue;
        g_text[g_text_count++] = {b, e};
    }
    std::fclose(maps);
    if (g_text_count == 0) {
        MS_LOGE("no executable mapping found for %s", info.dli_fname);
        return false;
    }
    MS_LOGI("libil2cpp: %s, base %p, %d exec ranges", info.dli_fname, info.dli_fbase, g_text_count);
    return true;
}

bool in_il2cpp_text(const void *p) {
    const auto a = reinterpret_cast<uintptr_t>(p);
    for (int i = 0; i < g_text_count; ++i) {
        if (a >= g_text[i].begin && a < g_text[i].end) return true;
    }
    return false;
}

void *find_class(const char *image_name, const char *ns, const char *name) {
    size_t count = 0;
    const void **assemblies = api.domain_get_assemblies(api.domain_get(), &count);
    if (!assemblies || count == 0 || count > 4096) return nullptr;
    for (size_t i = 0; i < count; ++i) {
        const void *image = api.assembly_get_image(assemblies[i]);
        if (!image) continue;
        if (image_name) {
            const char *n = api.image_get_name(image);
            if (!n || std::strcmp(n, image_name) != 0) continue;
        }
        if (void *k = api.class_from_name(image, ns, name)) return k;
    }
    MS_LOGE("class not found: [%s] %s.%s", image_name ? image_name : "*", ns, name);
    return nullptr;
}

const void *find_method(void *klass, const char *name, int param_count,
                        const char *const *param_types) {
    if (!klass) return nullptr;
    const void *found = nullptr;
    int matches = 0;
    void *iter = nullptr;
    int guard = 0;
    while (const void *m = api.class_get_methods(klass, &iter)) {
        if (++guard > 20000) break;
        const char *mn = api.method_get_name(m);
        if (!mn || std::strcmp(mn, name) != 0) continue;
        if (static_cast<int>(api.method_get_param_count(m)) != param_count) continue;
        if (param_types) {
            bool all = true;
            for (int p = 0; p < param_count && all; ++p) {
                all = type_name_equals(api.method_get_param(m, static_cast<uint32_t>(p)), param_types[p]);
            }
            if (!all) continue;
        }
        found = m;
        ++matches;
    }
    if (matches != 1) {
        MS_LOGE("method %s/%d: %d matches", name, param_count, matches);
        return nullptr;
    }
    void *code = method_pointer(found);
    if (!code || !in_il2cpp_text(code)) {
        MS_LOGE("method %s/%d: code pointer %p outside libil2cpp", name, param_count, code);
        return nullptr;
    }
    return found;
}

bool find_field(void *klass, const char *name, int expected_kind, bool expect_static, Field &out) {
    out = {};
    if (!klass) return false;
    void *f = api.class_get_field_from_name(klass, name);
    if (!f) {
        MS_LOGE("field not found: %s", name);
        return false;
    }
    const int kind = api.type_get_type(api.field_get_type(f));
    const bool is_static = (api.field_get_flags(f) & 0x0010) != 0;  // FIELD_ATTRIBUTE_STATIC
    if (kind != expected_kind || is_static != expect_static) {
        MS_LOGE("field %s: kind 0x%x static %d, expected kind 0x%x static %d",
                name, kind, is_static, expected_kind, expect_static);
        return false;
    }
    out.info = f;
    out.offset = api.field_get_offset(f);
    out.is_static = is_static;
    if (!is_static && (out.offset < 0x10 || out.offset > 0x10000)) {
        MS_LOGE("field %s: implausible offset 0x%zx", name, out.offset);
        out = {};
        return false;
    }
    return true;
}

}  // namespace ms::il2cpp
