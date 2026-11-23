#pragma once
// MethodInfo::methodPointer swap for IL2CPP hooks. No `.text` modification.
//
// Replaces Dobby inline hooks. libng (and any CRC-scanning anti-cheat) sees an
// unmodified libil2cpp.so; our replacement wins because the engine reads
// MethodInfo.methodPointer on every managed invoke.
//
// On this build the MethodInfo layout starts with:
//   [0x00] Il2CppMethodPointer methodPointer
//   [0x08] InvokerMethod invoker_method
//   [0x10] const char* name
//   [0x18] Il2CppClass* klass
//   [0x20] const Il2CppType* return_type
// The virtual slot is NOT patched here. For non-virtual MonoBehaviour messages
// like LateUpdate/Update the engine dispatches via methodPointer directly, so
// one write per method is enough.
#include <cstdint>

namespace method_swap {

// Patches MethodInfo.methodPointer. Returns the previous pointer (call this to
// forward to the original). Returns nullptr on invalid input.
inline void* install(void* method_info, void* replacement) {
    if (!method_info || !replacement) return nullptr;
    void** slot = reinterpret_cast<void**>(method_info);
    void* previous = *slot;
    __atomic_store_n(slot, replacement, __ATOMIC_RELEASE);
    return previous;
}

// Convenience: install, type-cast the previous pointer for the caller.
template<class Fn>
Fn install_typed(void* method_info, Fn replacement) {
    void* prev = install(method_info, reinterpret_cast<void*>(replacement));
    return reinterpret_cast<Fn>(prev);
}

} // namespace method_swap
