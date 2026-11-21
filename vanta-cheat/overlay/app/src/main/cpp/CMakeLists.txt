cmake_minimum_required(VERSION 3.22.1)
project(vanta)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(
    -fvisibility=hidden
    -fvisibility-inlines-hidden
    -ffunction-sections -fdata-sections
    -fno-rtti -fno-exceptions
    -Wall -Wno-unused-function -Wno-unused-variable
    -O2
)
add_link_options(-Wl,--gc-sections -Wl,--strip-all)

# ------------------------------------------------------------------
# libvantabridge.so — JNI, shm-ридер, aim через uinput, launcher helper'а
# ------------------------------------------------------------------
add_library(vantabridge SHARED
    native_bridge.cpp
    shm_reader.cpp
    uinput_aim.cpp
    ptrace_injector.cpp
    maps_util.cpp
)
target_include_directories(vantabridge PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/../../../../helper/src/main/cpp
)
target_link_libraries(vantabridge
    android log
)

# ------------------------------------------------------------------
# libvanta_helper.so — впихивается в процесс игры
# ------------------------------------------------------------------
add_library(vanta_helper SHARED
    ${CMAKE_SOURCE_DIR}/../../../../helper/src/main/cpp/helper.cpp
    ${CMAKE_SOURCE_DIR}/../../../../helper/src/main/cpp/il2cpp_api.cpp
)
target_include_directories(vanta_helper PRIVATE
    ${CMAKE_SOURCE_DIR}/../../../../helper/src/main/cpp
)
target_link_libraries(vanta_helper
    android log
    dl
)
