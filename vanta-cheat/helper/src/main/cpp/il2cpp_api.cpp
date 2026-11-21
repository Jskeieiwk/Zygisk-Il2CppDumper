// il2cpp_api.cpp — dlsym-резолв символов libil2cpp.so
#include "il2cpp_api.h"
#include <dlfcn.h>
#include <string.h>
#include <android/log.h>

#define LOGT(fmt, ...) __android_log_print(ANDROID_LOG_INFO, "vanta-il2cpp", fmt, ##__VA_ARGS__)

Il2CppApi g_il2cpp{};

bool il2cpp_api_load(void* h) {
    if (!h) return false;
    auto R = [&](const char* name) { return dlsym(h, name); };

    #define BIND(field, sym) \
        g_il2cpp.field = reinterpret_cast<decltype(g_il2cpp.field)>(R(sym)); \
        if (!g_il2cpp.field) { LOGT("missing symbol: %s", sym); return false; }

    BIND(domain_get,                   "il2cpp_domain_get");
    BIND(domain_get_assemblies,        "il2cpp_domain_get_assemblies");
    BIND(assembly_get_image,           "il2cpp_assembly_get_image");
    BIND(class_from_name,              "il2cpp_class_from_name");
    BIND(class_get_field_from_name,    "il2cpp_class_get_field_from_name");
    BIND(class_get_method_from_name,   "il2cpp_class_get_method_from_name");
    BIND(field_static_get_value,       "il2cpp_field_static_get_value");
    BIND(field_get_value,              "il2cpp_field_get_value");
    BIND(class_get_name,               "il2cpp_class_get_name");
    BIND(class_get_namespace,          "il2cpp_class_get_namespace");
    BIND(runtime_class_init,           "il2cpp_runtime_class_init");
    BIND(runtime_invoke,               "il2cpp_runtime_invoke");
    BIND(image_get_class_count,        "il2cpp_image_get_class_count");
    BIND(image_get_class,              "il2cpp_image_get_class");
    BIND(array_length,                 "il2cpp_array_length");
    BIND(thread_attach,                "il2cpp_thread_attach");
    BIND(thread_detach,                "il2cpp_thread_detach");
    #undef BIND

    // не критично — у некоторых игр нет / свои имена
    g_il2cpp.array_element_address =
        reinterpret_cast<decltype(g_il2cpp.array_element_address)>(R("il2cpp_array_element_address"));
    g_il2cpp.string_chars_utf8 =
        reinterpret_cast<decltype(g_il2cpp.string_chars_utf8)>(R("il2cpp_string_chars"));
    g_il2cpp.loaded = true;
    LOGT("il2cpp api loaded");
    return true;
}

// managed Il2CppString: [klass*][monitor*][int32 length][uint16 chars...]
// длина — 32-битная, затем UTF-16 данные
void il2cpp_string_to_cstr(Il2CppString* s, char* out, size_t cap) {
    if (!s || !out || cap == 0) { if (out && cap) out[0] = 0; return; }
    auto p = reinterpret_cast<const uint8_t*>(s);
    int32_t len = *reinterpret_cast<const int32_t*>(p + 0x10);
    auto src = reinterpret_cast<const uint16_t*>(p + 0x14);
    size_t j = 0;
    for (int32_t i = 0; i < len && j + 1 < cap; ++i) {
        uint16_t c = src[i];
        if (c < 0x80) {
            out[j++] = static_cast<char>(c);
        } else if (c < 0x800) {
            if (j + 2 >= cap) break;
            out[j++] = static_cast<char>(0xC0 | (c >> 6));
            out[j++] = static_cast<char>(0x80 | (c & 0x3F));
        } else {
            if (j + 3 >= cap) break;
            out[j++] = static_cast<char>(0xE0 | (c >> 12));
            out[j++] = static_cast<char>(0x80 | ((c >> 6) & 0x3F));
            out[j++] = static_cast<char>(0x80 | (c & 0x3F));
        }
    }
    out[j] = 0;
}
