cmake_minimum_required(VERSION 3.20)
project(RayTracing)

set(CMAKE_CXX_STANDARD 20)

include_directories(
        lib/glm
        lib/SDL2-2.0.16/include
        lib/stb
)

link_directories(
        lib/SDL2-2.0.16/lib/x64
)

add_executable(
        RayTracing
        WIN32
        src/main.cpp
        src/settings/settings.h
        src/settings/camera_settings.h
        src/renderer.h
        src/renderer.cpp
        src/ray.h
        src/ray.cpp
        src/objects/hittable.h
        src/objects/hittable_list.h
        src/objects/hittable_list.cpp
        src/objects/bvh_node.h
        src/objects/bvh_node.cpp
        src/objects/sphere.h
        src/objects/sphere.cpp
        src/objects/rect_yz.h
        src/objects/rect_yz.cpp
        src/objects/rect_xz.h
        src/objects/rect_xz.cpp
        src/objects/rect_xy.h
        src/objects/rect_xy.cpp
        src/objects/box.h
        src/objects/box.cpp
        src/structs/hit_record.h
        src/structs/thread_info.h
        src/structs/scatter_info.h
        src/camera.h
        src/camera.cpp
        src/scene.h
        src/scene.cpp
        src/aabb.h
        src/aabb.cpp
        src/texture/texture.h
        src/texture/texture_solid_color.h
        src/texture/texture_checkered.h
        src/texture/texture_checkered.cpp
        src/texture/texture_noise.h
        src/texture/texture_image.h
        src/texture/texture_image.cpp
        src/material/material.h
        src/material/material_diffuse.h
        src/material/material_diffuse.cpp
        src/material/material_metal.h
        src/material/material_metal.cpp
        src/material/material_refractive.h
        src/material/material_refractive.cpp
        src/material/material_diffuse_light.h
        src/material/material_diffuse_light.cpp
        src/utils/utils.h
        src/utils/utils.cpp
        src/utils/perlin.h
        src/utils/perlin.cpp
)

target_link_libraries(RayTracing SDL2.lib)
