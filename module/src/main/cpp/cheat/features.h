#pragma once

#include <cstddef>

#include "hook.h"

namespace ms::features {

// Appends the game hooks (requires game::resolve() to have succeeded). Returns the count added.
size_t fill_hook_specs(hook::Spec *out, size_t capacity);

// Enables hook logic. Until then every hook passes straight through to the game.
void set_ready();

}  // namespace ms::features
