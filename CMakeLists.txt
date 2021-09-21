cmake_minimum_required(VERSION 3.20)
project(RayTracing)

set(CMAKE_CXX_STANDARD 20)

include_directories(
        lib/glm
        lib/SDL/include
        lib/stb
)

# https://www.libsdl.org/download-2.0.php
link_directories(
        lib/SDL/lib/x64
)

FILE(GLOB_RECURSE PROJECT_SOURCES src/*cpp src/*h)
add_executable(RayTracing WIN32 ${PROJECT_SOURCES})

target_link_libraries(RayTracing SDL2.lib)
