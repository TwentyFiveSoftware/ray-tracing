cmake_minimum_required(VERSION 3.20)
project(RayTracing)

set(CMAKE_CXX_STANDARD 20)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=x86-64 -mavx2")

include_directories(
        lib/glm
        lib/stb
)

FILE(GLOB_RECURSE PROJECT_SOURCES src/*cpp src/*h)
add_executable(RayTracing ${PROJECT_SOURCES})
