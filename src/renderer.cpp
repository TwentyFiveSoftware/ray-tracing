#include "renderer.h"
#include "utils.h"

glm::vec3 calculateRayColor(const Ray &ray, const Hittable &world) {
    HitRecord record = {};
    if (world.hit(ray, 0, INFINITY, record)) {
        return 0.5f * (record.normal + 1.0f);
    }

    // background: linear interpolation between white and blue based on normalized y coordinate of direction vector
    float t = 0.5f * (glm::normalize(ray.getDirection()).y + 1.0f);
    return (1.0f - t) * glm::vec3(1.0f, 1.0f, 1.0f) + t * glm::vec3(0.5f, 0.7f, 1.0f);
}

void renderThreadEntryPoint(uint16_t startY, uint16_t endY,
                            std::array<Pixel, Settings::WIDTH * Settings::HEIGHT>* pixels,
                            std::atomic<uint32_t>* pixelsRendered,
                            const HittableList &world,
                            const Camera &camera) {

    for (uint16_t y = startY; y < endY; y++) {
        for (uint16_t x = 0; x < Settings::WIDTH; x++) {
            glm::vec3 pixelColor;

            for (int sample = 0; sample < Settings::SAMPLES_PER_PIXEL; sample++) {
                float u = (float(x) + randomFloat(0, 1)) / Settings::WIDTH;
                float v = (float(y) + randomFloat(0, 1)) / Settings::HEIGHT;

                pixelColor += calculateRayColor(camera.getRay(u, v), world);
            }

            pixelColor = glm::vec3(
                    clamp(pixelColor.x / Settings::SAMPLES_PER_PIXEL, 0, 1),
                    clamp(pixelColor.y / Settings::SAMPLES_PER_PIXEL, 0, 1),
                    clamp(pixelColor.z / Settings::SAMPLES_PER_PIXEL, 0, 1)
            );

            pixels->at(y * Settings::WIDTH + x) = {.pos = {x, y}, .color = pixelColor};
        }

        *pixelsRendered += Settings::WIDTH;
    }
}
