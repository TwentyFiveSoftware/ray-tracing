#pragma once

#include "../objects/hittable_list.h"
#include "../camera.h"

struct ThreadInfo {
    unsigned char* pixels;
    std::atomic <uint16_t>* nextPixelRowToRender;
    std::atomic <uint32_t>* pixelsRendered;
    const HittableList &world;
    const Camera &camera;
};
