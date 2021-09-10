#pragma once

#include "../objects/hittable_list.h"
#include "../camera.h"

struct ThreadInfo {
    unsigned char* pixels;
    glm::vec3* summedSampleDataPerPixel;
    std::atomic<uint16_t>* nextPixelRowToRender;
    uint16_t* currentPixelSample;
    const HittableList &world;
    const Camera &camera;
};
