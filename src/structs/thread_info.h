#pragma once

#include "../scene.h"

struct ThreadInfo {
    unsigned char* pixels;
    glm::vec3* summedSampleDataPerPixel;
    std::atomic<uint16_t>* nextPixelRowToRender;
    uint16_t* currentPixelSample;
    const Scene &scene;
};
