#include "renderer.h"
#include "settings/camera.h"

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
                            const HittableList &world) {

    for (uint16_t y = startY; y < endY; y++) {
        for (uint16_t x = 0; x < Settings::WIDTH; x++) {
            float u = float(x) / Settings::WIDTH;
            float v = float(y) / Settings::HEIGHT;

            glm::vec3 direction = Camera::UPPER_LEFT_CORNER
                                  + glm::vec3(Camera::VIEWPORT_WIDTH, 0.0f, 0.0f) * u
                                  - glm::vec3(0.0f, Camera::VIEWPORT_HEIGHT, 0.0f) * v
                                  - Camera::ORIGIN;

            Ray ray(Camera::ORIGIN, direction);
            glm::vec3 pixelColor = calculateRayColor(ray, world);

            pixels->at(y * Settings::WIDTH + x) = {.pos = {x, y}, .color = pixelColor};
        }

        *pixelsRendered += Settings::WIDTH;
    }
}
