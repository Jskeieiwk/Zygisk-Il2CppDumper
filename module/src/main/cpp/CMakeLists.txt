cmake_minimum_required(VERSION 3.18.1)

if (NOT DEFINED MODULE_NAME)
    set(MODULE_NAME "cloud_cheat")
endif ()
project(${MODULE_NAME})

set(CMAKE_CXX_STANDARD 20)

set(LINKER_FLAGS "-ffixed-x18 -Wl,--hash-style=both")
set(C_FLAGS "-Werror=format -fdata-sections -ffunction-sections")
set(CXX_FLAGS "${CXX_FLAGS} -fno-exceptions -fno-rtti")

if (NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(C_FLAGS "${C_FLAGS} -O2 -fvisibility=hidden -fvisibility-inlines-hidden")
    set(LINKER_FLAGS "${LINKER_FLAGS} -Wl,-exclude-libs,ALL -Wl,--gc-sections -Wl,--strip-all")
else ()
    set(C_FLAGS "${C_FLAGS} -O0")
endif ()

set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   ${C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${C_FLAGS} ${CXX_FLAGS}")

set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${LINKER_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS    "${CMAKE_EXE_LINKER_FLAGS}    ${LINKER_FLAGS}")

include_directories(xdl/include cheat)

aux_source_directory(xdl xdl-src)

set(CHEAT_SRC
        cheat/cheat.cpp
        cheat/features.cpp
        cheat/overlay.cpp
        cheat/hook.cpp
        cheat/il2cpp_api.cpp)

# ─────────────────────────── payload library ──────────────────────────────
add_library(${MODULE_NAME} SHARED
        main.cpp
        hack.cpp
        ${CHEAT_SRC}
        ${xdl-src})

target_link_libraries(${MODULE_NAME} log EGL GLESv3)

# ─────────────────────────── root ptrace injector ──────────────────────────
# Named lib<name>.so so Android's APK installer extracts it into
# nativeLibraryDir alongside the payload.  Linked as -pie so it's actually
# an executable; the MainActivity renames + chmods +x and runs it under su.
add_executable(cloud_injector injector/injector.cpp)
set_target_properties(cloud_injector PROPERTIES
        OUTPUT_NAME "cloud_injector.so"
        PREFIX "lib")
target_link_options(cloud_injector PRIVATE "-pie" "-static-libstdc++")
target_link_libraries(cloud_injector log)
