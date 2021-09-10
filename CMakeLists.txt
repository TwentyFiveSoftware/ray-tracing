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

add_executable(
        RayTracing
        WIN32
        src/main.cpp
        src/settings/settings.h
        src/structs/pixel.h
        src/settings/camera_settings.h
        src/renderer.h
        src/renderer.cpp
        src/ray.h
        src/ray.cpp
        src/objects/hittable.h
        src/objects/hittable_list.h
        src/objects/hittable_list.cpp
        src/objects/sphere.h
        src/objects/sphere.cpp
        src/structs/hit_record.h
        src/utils.h
        src/utils.cpp
        src/camera.h
        src/camera.cpp
)

target_link_libraries(RayTracing SDL2.lib)
