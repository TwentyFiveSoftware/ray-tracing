cmake_minimum_required(VERSION 3.20)
project(RayTracing)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native -flto")

include_directories(
        lib/stb
)

FILE(GLOB_RECURSE PROJECT_SOURCES src/*cpp src/*h)
add_executable(RayTracing ${PROJECT_SOURCES})
