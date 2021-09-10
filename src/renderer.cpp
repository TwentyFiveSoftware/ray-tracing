#include "renderer.h"
#include "utils.h"
#include "settings/settings.h"
#include <iostream>

glm::vec3 calculateRayColor(const Ray &ray, const Hittable &world, uint16_t depth) {
    HitRecord record = {};

    if (depth >= Settings::MAX_DEPTH) {
        return {0.0f, 0.0f, 0.0f};
    }

    if (world.hit(ray, 0.001, INFINITY, record)) {
        ScatterInfo scatterInfo = record.materialPtr->scatter(ray, record.pos, record.normal);

        if (scatterInfo.doesScatter) {
            return scatterInfo.attenuation * calculateRayColor(scatterInfo.scatteredRay, world, depth + 1);
        }

        return {0.0f, 0.0f, 0.0f};
    }

    // background: linear interpolation between white and blue based on normalized y coordinate of direction vector
    float t = 0.5f * (glm::normalize(ray.getDirection()).y + 1.0f);
    return (1.0f - t) * glm::vec3(1.0f, 1.0f, 1.0f) + t * glm::vec3(0.5f, 0.7f, 1.0f);
}

void writeColor(uint16_t x, uint16_t y, glm::vec3 color, unsigned char* pixels) {
    color = glm::sqrt(color);
    color = glm::clamp(color, 0.0f, 1.0f);
    color *= 0xFF;

    int index = (y * Settings::WIDTH + x) * 3;

    pixels[index + 0] = static_cast<unsigned char>(color.x);
    pixels[index + 1] = static_cast<unsigned char>(color.y);
    pixels[index + 2] = static_cast<unsigned char>(color.z);
}

void renderThreadFunction(const ThreadInfo &threadInfo) {
    uint16_t y = (*threadInfo.nextPixelRowToRender)++;

    while (y < Settings::HEIGHT) {
        for (uint16_t x = 0; x < Settings::WIDTH; x++) {
            float u = (float(x) + randomFloat()) / Settings::WIDTH;
            float v = (float(y) + randomFloat()) / Settings::HEIGHT;

            threadInfo.summedSampleDataPerPixel[y * Settings::WIDTH + x] +=
                    calculateRayColor(threadInfo.camera.getRay(u, v), threadInfo.world, 0);

            glm::vec3 pixelColor =
                    threadInfo.summedSampleDataPerPixel[y * Settings::WIDTH + x] /
                    float(*threadInfo.currentPixelSample);

            writeColor(x, y, pixelColor, threadInfo.pixels);
        }

        y = (*threadInfo.nextPixelRowToRender)++;
    }
}
