#pragma once

#include <cstddef>

namespace ms::hook {

struct Spec {
    const char *name;
    void *target;        // function entry to patch
    void *replacement;
    void **original;     // receives the trampoline
};

// Installs every hook or none: on any failure the bytes already patched are restored
// and every *original is reset to nullptr. Trampolines from a failed attempt are leaked.
bool install_all(Spec *specs, size_t count);

}  // namespace ms::hook
