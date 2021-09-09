cmake_minimum_required(VERSION 3.20)
project(RayTracing)

set(CMAKE_CXX_STANDARD 20)

include_directories(
        lib/glm
        lib/SDL2-2.0.16/include
)

link_directories(
        lib/SDL2-2.0.16/lib/x64
)

add_executable(RayTracing WIN32 src/main.cpp)

target_link_libraries(RayTracing SDL2.lib)
