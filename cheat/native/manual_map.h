#pragma once
// Reflective loader: maps our payload .so into the target process without ever
// calling the Android linker's dlopen. No soinfo entry is created, so shadowhook's
// soinfo::call_constructors intercept (used by libng's dl_init callback) never
// fires for us.
//
// Flow:
//   1. Read .so bytes locally (loader process).
//   2. Parse ELF: enumerate PT_LOAD segments, DYNAMIC entries.
//   3. Remote mmap (via caller) a single RW region large enough for all LOAD
//      segments at their virtual offsets.
//   4. Bulk-write each segment with process_vm_writev (fast; no PTRACE_POKEDATA
//      per word).
//   5. Apply R_AARCH64_RELATIVE / GLOB_DAT / JUMP_SLOT / ABS64 relocations.
//      Externs are resolved by matching the loader's own dlsym addresses to the
//      game's mappings of the same libraries.
//   6. Remote mprotect each segment to its final PT_LOAD PF_* flags.
//   7. Call every DT_INIT_ARRAY entry via `caller`.
//
// The payload must not rely on linker-provided services inside:
//   - no thread_local variables
//   - no __cxa_atexit registration against __dso_handle
//   - no unwinding into the payload
// All of the above are already true for the current payload.
#include <cstdint>
#include <functional>
#include <initializer_list>
#include <string>
#include <sys/types.h>

namespace manual_map {

// Callback invoked for every remote function call the mapper needs.
// Matches the signature of Trace::call in injector.cpp.
using RemoteCaller = std::function<uintptr_t(uintptr_t, std::initializer_list<uintptr_t>)>;

// Perform a reflective load of `so_path` into process `pid`. The caller is
// expected to have ptrace-attached `pid` before invoking and to detach only
// after this returns. Returns the chosen remote base address.
uintptr_t load(pid_t pid, const RemoteCaller& caller, const std::string& so_path);

} // namespace manual_map
