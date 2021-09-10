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

void writeColor(uint16_t x, uint16_t y, glm::vec3 color, unsigned char* pixels) {
    color = glm::clamp(color, 0.0f, 1.0f);
    color *= 0xFF;

    int index = (y * Settings::WIDTH + x) * 3;

    pixels[index + 0] = static_cast<unsigned char>(color.x);
    pixels[index + 1] = static_cast<unsigned char>(color.y);
    pixels[index + 2] = static_cast<unsigned char>(color.z);
}

void renderThreadEntryPoint(uint16_t startY, uint16_t endY,
                            unsigned char* pixels,
                            std::atomic<uint32_t>* pixelsRendered,
                            const HittableList &world,
                            const Camera &camera) {

    for (uint16_t y = startY; y < endY; y++) {
        for (uint16_t x = 0; x < Settings::WIDTH; x++) {
            glm::vec3 pixelColor = glm::vec3(0.0f, 0.0f, 0.0f);

            for (uint16_t sample = 0; sample < Settings::SAMPLES_PER_PIXEL; sample++) {
                float u = (float(x) + randomFloat(0, 1)) / Settings::WIDTH;
                float v = (float(y) + randomFloat(0, 1)) / Settings::HEIGHT;

                pixelColor += calculateRayColor(camera.getRay(u, v), world);
            }

            pixelColor /= Settings::SAMPLES_PER_PIXEL;

            writeColor(x, y, pixelColor, pixels);
        }

        *pixelsRendered += Settings::WIDTH;
    }
}
