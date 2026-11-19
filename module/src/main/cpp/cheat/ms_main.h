#pragma once

namespace ms {

// Blocking: waits for il2cpp, resolves the game, installs every hook. Call from a background thread.
void start(void *il2cpp_handle);

}  // namespace ms
