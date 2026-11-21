// il2cpp_api.h — минимальные декларации IL2CPP API, разрешаемые через dlsym libil2cpp.so.
// подробный интерфейс: il2cpp-api-functions.h в zygisk-дампере, но нам нужна только выборка.
#pragma once

#include <stdint.h>
#include <stddef.h>

struct Il2CppDomain;
struct Il2CppAssembly;
struct Il2CppImage;
struct Il2CppClass;
struct Il2CppObject;
struct Il2CppString;
struct Il2CppArray;
struct Il2CppType;
struct FieldInfo;
struct MethodInfo;
struct Il2CppException;

struct Il2CppVector3 { float x, y, z; };
struct Il2CppVector2 { float x, y; };
struct Il2CppQuaternion { float x, y, z, w; };

// сигнатуры загрузчика; присваиваются в helper.cpp через dlsym
struct Il2CppApi {
    Il2CppDomain*   (*domain_get)();
    const Il2CppAssembly** (*domain_get_assemblies)(const Il2CppDomain* domain, size_t* size);
    const Il2CppImage* (*assembly_get_image)(const Il2CppAssembly* assembly);
    Il2CppClass*    (*class_from_name)(const Il2CppImage* image, const char* namespaze, const char* name);
    FieldInfo*      (*class_get_field_from_name)(Il2CppClass* klass, const char* name);
    const MethodInfo* (*class_get_method_from_name)(Il2CppClass* klass, const char* name, int argsCount);
    void            (*field_static_get_value)(FieldInfo* field, void* value);
    void            (*field_get_value)(Il2CppObject* obj, FieldInfo* field, void* value);
    const char*     (*class_get_name)(Il2CppClass* klass);
    const char*     (*class_get_namespace)(Il2CppClass* klass);
    void            (*runtime_class_init)(Il2CppClass* klass);
    Il2CppObject*   (*runtime_invoke)(const MethodInfo* method, void* obj, void** params, Il2CppException** exc);
    void*           (*method_get_from_name)(Il2CppClass* klass, const char* name, int argsCount);
    int             (*image_get_class_count)(const Il2CppImage* image);
    Il2CppClass*    (*image_get_class)(const Il2CppImage* image, size_t index);
    uint32_t        (*array_length)(Il2CppArray* array);
    void*           (*array_element_address)(Il2CppArray* array, uint32_t index);
    const char*     (*string_chars_utf8)(Il2CppString* str);
    void            (*thread_attach)(Il2CppDomain* domain);
    void            (*thread_detach)(void* thread);

    // extras для списков: мы не дёргаем Add/Remove — только Count/Item
    // всё делается через runtime_invoke на MethodInfo из class_get_method_from_name.
    bool loaded = false;
};

extern Il2CppApi g_il2cpp;

bool il2cpp_api_load(void* libil2cpp_handle);

// утилита: достать managed string → наш char-буфер
void il2cpp_string_to_cstr(Il2CppString* s, char* out, size_t cap);
