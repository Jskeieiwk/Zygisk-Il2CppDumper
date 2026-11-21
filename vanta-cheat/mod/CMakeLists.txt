cmake_minimum_required(VERSION 3.22)
project(vanta)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if(NOT CMAKE_ANDROID_ARCH_ABI STREQUAL "arm64-v8a")
    message(FATAL_ERROR "vanta требует arm64-v8a")
endif()

add_compile_options(
    -fvisibility=hidden
    -fvisibility-inlines-hidden
    -ffunction-sections -fdata-sections
    -Wall -Wno-unused-function -Wno-unused-variable -Wno-c++11-narrowing
    -O2
)
add_link_options(-Wl,--gc-sections -Wl,--strip-all)

# ---- ImGui (FetchContent) ----
include(FetchContent)
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG        v1.91.5
    GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(imgui)

# ---- libvanta.so (инжектится в игру) ----
set(IMGUI_SRC
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_demo.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

add_library(vanta SHARED
    libvanta/entry.cpp
    libvanta/state.cpp
    libvanta/gl_hook.cpp
    libvanta/plt_hook.cpp
    libvanta/renderer.cpp
    libvanta/menu.cpp
    libvanta/esp.cpp
    libvanta/input.cpp
    libvanta/aim.cpp
    libvanta/game.cpp
    ../helper/src/main/cpp/il2cpp_api.cpp
    ${IMGUI_SRC}
)
target_compile_definitions(vanta PRIVATE
    IMGUI_IMPL_OPENGL_ES3
    IMGUI_DISABLE_OBSOLETE_FUNCTIONS
)
target_include_directories(vanta PRIVATE
    libvanta
    ../helper/src/main/cpp
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
)
target_link_libraries(vanta
    android log dl
    EGL GLESv3
)
set_target_properties(vanta PROPERTIES OUTPUT_NAME "vanta")

# ---- inject-arm64 standalone ----
add_executable(inject-arm64 injector/inject.cpp)
target_link_libraries(inject-arm64 log dl)
