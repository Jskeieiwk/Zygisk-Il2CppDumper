#include "il2cpp_api.h"
#include "../xdl/include/xdl.h"
#include "../log.h"
#include <cstring>

#define DO_API(r, n, p) r (*n) p = nullptr
#include "../il2cpp-api-functions.h"
#undef DO_API

static uintptr_t s_il2cpp_base = 0;

void il2cpp_api_init(void *handle) {
#define DO_API(r, n, p) {                               \
    n = (r (*) p)xdl_sym(handle, #n, nullptr);          \
    if (!n) LOGW("il2cpp api not found: %s", #n);       \
}
#include "../il2cpp-api-functions.h"
#undef DO_API
}

uintptr_t il2cpp_base() { return s_il2cpp_base; }
void il2cpp_set_base(uintptr_t b) { s_il2cpp_base = b; }

Il2CppClass *find_class(const char *image_name, const char *ns, const char *name) {
    if (!il2cpp_domain_get || !il2cpp_domain_get_assemblies || !il2cpp_assembly_get_image || !il2cpp_class_from_name)
        return nullptr;
    auto domain = il2cpp_domain_get();
    if (!domain) return nullptr;
    size_t n_ass = 0;
    auto assemblies = il2cpp_domain_get_assemblies(domain, &n_ass);
    for (size_t i = 0; i < n_ass; ++i) {
        auto image = il2cpp_assembly_get_image(assemblies[i]);
        if (!image) continue;
        if (image_name) {
            auto n = il2cpp_image_get_name(image);
            if (!n || strcmp(n, image_name) != 0) continue;
        }
        auto k = il2cpp_class_from_name(image, ns ? ns : "", name);
        if (k) return k;
    }
    return nullptr;
}

Il2CppClass *find_class_simple(const char *name) {
    return find_class(nullptr, "", name);
}

const MethodInfo *find_method(Il2CppClass *klass, const char *name, int args) {
    if (!klass || !il2cpp_class_get_method_from_name) return nullptr;
    return il2cpp_class_get_method_from_name(klass, name, args);
}

FieldInfo *find_field(Il2CppClass *klass, const char *name) {
    if (!klass || !il2cpp_class_get_field_from_name) return nullptr;
    return il2cpp_class_get_field_from_name(klass, name);
}

int get_field_offset(FieldInfo *f) {
    if (!f || !il2cpp_field_get_offset) return -1;
    return il2cpp_field_get_offset(f);
}

void *field_addr(void *instance, int offset) {
    return (uint8_t*)instance + offset;
}
