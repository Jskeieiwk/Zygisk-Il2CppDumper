#ifndef CLOUD_CHEAT_IL2CPP_API_H
#define CLOUD_CHEAT_IL2CPP_API_H

#include <cstdint>
#include <cstddef>
#include "../il2cpp-class.h"

#define DO_API(r, n, p) extern r (*n) p
#include "../il2cpp-api-functions.h"
#undef DO_API

void il2cpp_api_init(void *handle);

uintptr_t il2cpp_base();
void       il2cpp_set_base(uintptr_t b);

Il2CppClass *find_class(const char *image_name, const char *ns, const char *name);
Il2CppClass *find_class_simple(const char *name);

const MethodInfo *find_method(Il2CppClass *klass, const char *name, int args);
FieldInfo        *find_field(Il2CppClass *klass, const char *name);

int   get_field_offset(FieldInfo *f);
void *field_addr(void *instance, int offset);

template <typename T>
T  read_field(void *instance, int offset) { return *(T*)((uint8_t*)instance + offset); }

template <typename T>
void write_field(void *instance, int offset, T value) { *(T*)((uint8_t*)instance + offset) = value; }

#endif
