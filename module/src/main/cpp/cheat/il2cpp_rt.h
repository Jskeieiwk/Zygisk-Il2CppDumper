#pragma once

// Minimal il2cpp runtime access by name. Every game symbol is resolved through the
// exported il2cpp_* API at runtime, so no RVA or field offset is hardcoded.

#include <cstddef>
#include <cstdint>

namespace ms::il2cpp {

// Il2CppTypeEnum values (il2cpp-class.h in this repo).
enum TypeKind : int {
    kBoolean = 0x02,
    kI4 = 0x08,
    kR4 = 0x0c,
    kString = 0x0e,
    kValueType = 0x11,
    kClass = 0x12,
    kIntPtr = 0x18,
};

struct Api {
    bool (*is_vm_thread)(void *thread);
    void *(*domain_get)();
    const void **(*domain_get_assemblies)(const void *domain, size_t *size);
    const void *(*assembly_get_image)(const void *assembly);
    const char *(*image_get_name)(const void *image);
    void *(*class_from_name)(const void *image, const char *ns, const char *name);
    const void *(*class_get_methods)(void *klass, void **iter);
    const char *(*method_get_name)(const void *method);
    uint32_t (*method_get_param_count)(const void *method);
    const void *(*method_get_param)(const void *method, uint32_t index);
    uint32_t (*method_get_flags)(const void *method, uint32_t *iflags);
    char *(*type_get_name)(const void *type);
    int (*type_get_type)(const void *type);
    void (*free_mem)(void *ptr);
    void *(*class_get_field_from_name)(void *klass, const char *name);
    size_t (*field_get_offset)(void *field);
    const void *(*field_get_type)(void *field);
    int (*field_get_flags)(void *field);
    void (*field_static_get_value)(void *field, void *value);
    void (*field_static_set_value)(void *field, void *value);
    const void *(*class_get_type)(void *klass);
    void *(*type_get_object)(const void *type);
    void *(*string_new)(const char *str);
    uint32_t (*array_length)(void *array);
    void (*runtime_class_init)(void *klass);
    void *(*thread_attach)(void *domain);
    void (*thread_detach)(void *thread);
};

extern Api api;

// Loads every function above from libil2cpp. Returns false if any is missing.
bool load_api(void *il2cpp_handle);

// Executable range of libil2cpp.so, used to validate method pointers.
bool init_module_range(void *any_il2cpp_symbol);
bool in_il2cpp_text(const void *p);

// image_name == nullptr searches every loaded image.
void *find_class(const char *image_name, const char *ns, const char *name);

// param_types: exact il2cpp type names ("System.String"), or nullptr to only match the count.
// Returns the MethodInfo*, or nullptr if missing, ambiguous or its code lies outside libil2cpp.
const void *find_method(void *klass, const char *name, int param_count,
                        const char *const *param_types = nullptr);

inline void *method_pointer(const void *method_info) {
    // MethodInfo::methodPointer is the first member in every il2cpp version with metadata v24+.
    return method_info ? *reinterpret_cast<void *const *>(method_info) : nullptr;
}

struct Field {
    void *info = nullptr;
    size_t offset = 0;      // instance fields: byte offset inside the object
    bool is_static = false;
    bool ok() const { return info != nullptr; }
};

// Fails if the field is missing, has another type kind or another static-ness.
bool find_field(void *klass, const char *name, int expected_kind, bool expect_static, Field &out);

// Il2CppArray on 64-bit: klass, monitor, bounds, max_length, then elements at 0x20.
constexpr size_t kArrayDataOffset = 0x20;

}  // namespace ms::il2cpp
