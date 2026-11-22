#ifndef CLOUD_CHEAT_HOOK_H
#define CLOUD_CHEAT_HOOK_H

#include <cstdint>

bool inline_hook(void *target, void *hook, void **trampoline_out);
void patch_bytes(void *addr, const void *bytes, size_t len);
void patch_u32 (void *addr, uint32_t v);

void *resolve_rva(uint64_t rva);

#endif
