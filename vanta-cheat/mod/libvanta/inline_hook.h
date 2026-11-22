// inline_hook.h — минимальный aarch64 inline hook через перезапись 16 байт префикса.
#pragma once

namespace vanta {
// заменяет первые 16 байт `target` на прыжок в `new_fn`.
// в *orig_trampoline пишет адрес трамплина, через который вызывать оригинал.
// возвращает true при успехе. требует: первые 4 инструкции target не PC-relative.
bool inline_hook(void* target, void* new_fn, void** orig_trampoline);
}
