#include "renderer.h"
#include "utils/utils.h"
#include "settings/settings.h"
#include <iostream>

glm::vec3 calculateRayColor(const Ray &ray, const glm::vec3 &backgroundColor, const Hittable &objects, uint16_t depth) {
    if (depth >= Settings::MAX_DEPTH)
        return {0.0f, 0.0f, 0.0f};

    HitRecord record = {};

    if (!objects.hit(ray, 0.001, INFINITY, record))
        return backgroundColor;

    glm::vec3 emission = record.materialPtr->emitted(record.pos, record.uv);
    ScatterInfo scatterInfo = record.materialPtr->scatter(ray, record.pos, record.normal, record.uv, record.frontFace);

    if (!scatterInfo.doesScatter)
        return emission;

    return emission + scatterInfo.attenuation *
                      calculateRayColor(scatterInfo.scatteredRay, backgroundColor, objects, depth + 1);
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
                    calculateRayColor(threadInfo.scene.getCamera().getRay(u, v), threadInfo.scene.getBackgroundColor(),
                                      threadInfo.scene.getObjects(), 0);

            glm::vec3 pixelColor =
                    threadInfo.summedSampleDataPerPixel[y * Settings::WIDTH + x] /
                    float(*threadInfo.currentPixelSample);

            writeColor(x, y, pixelColor, threadInfo.pixels);
        }

        y = (*threadInfo.nextPixelRowToRender)++;
    }
}
