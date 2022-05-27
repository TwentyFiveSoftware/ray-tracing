cmake_minimum_required(VERSION 3.20)
project(RayTracing)

set(CMAKE_CXX_STANDARD 20)

include_directories(
        lib/glm
        lib/stb
)

FILE(GLOB_RECURSE PROJECT_SOURCES src/*cpp src/*h)
add_executable(RayTracing ${PROJECT_SOURCES} src/main.cpp src/ray.cpp src/renderer.cpp src/camera.cpp src/camera.h src/constants.h src/utils.cpp src/utils.h src/sphere.cpp src/sphere.h src/hit_record.h src/scene.cpp src/scene.h src/material.h src/scatter.h src/scatter.cpp)
