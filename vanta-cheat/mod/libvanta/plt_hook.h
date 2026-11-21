// plt_hook.h — минимальный PLT/GOT хукер aarch64 для ELF .so в ARM-64 Android.
// идея: перезаписываем в чужой .so (например libil2cpp.so) слот GOT импорта,
// адрес которого разрешается в нужный символ (напр. eglSwapBuffers).
// возвращает предыдущее значение (ориг. указатель).
#pragma once

#include <stdint.h>

namespace vanta {

// идёт по .rela.plt / .rela.dyn целевой библиотеки, если находит JUMP_SLOT с именем sym_name —
// переписывает указатель и возвращает старый.
// so_name — соответствует подстроке в /proc/self/maps.
// при ошибке возвращает nullptr.
void* plt_hook(const char* so_name, const char* sym_name, void* new_fn);

} // namespace vanta
