// maps_util.h — поиск pid процесса игры и адресов библиотек в нём.
#pragma once

#include <stdint.h>
#include <sys/types.h>
#include <string>

namespace vanta {

// находит pid первого процесса с таким именем (cmdline startsWith)
pid_t find_pid_by_package(const char* package_name);

// находит базовый адрес модуля (libXXX.so) в адресном пространстве pid
uintptr_t find_module_base(pid_t pid, const char* soname);

// возвращает remote-адрес экспортированного символа в чужом процессе:
// base(libc.so в их maps) + offset(libc.so в наших maps для dlsym в себе)
uintptr_t get_remote_symbol(pid_t pid, const char* lib, const char* sym);

} // namespace vanta
