#include "renderer.h"
#include "constants.h"
#include "hit_record.h"
#include "scatter.h"

HitRecord rayHitsScene(const Scene &scene, const Ray &ray, float tMin, float tMax) {
    HitRecord currentHitRecord = {.t = tMax};

    for (const Sphere &sphere: scene.getSpheres()) {
        HitRecord hitRecord = sphere.rayHitsSphere(ray, tMin, currentHitRecord.t);
        if (hitRecord.hit) {
            currentHitRecord = hitRecord;
        }
    }

    return currentHitRecord;
}

glm::vec3 calculateRayColor(const Scene &scene, const Ray &ray, int32_t depth) {
    if (depth <= 0) {
        return {0.0f, 0.0f, 0.0f};
    }

    HitRecord hitRecord = rayHitsScene(scene, ray, 0.001f, std::numeric_limits<float>::infinity());
    if (hitRecord.hit) {
        ScatterInfo scatterInfo = scatter(ray, hitRecord);

        if (scatterInfo.doesScatter) {
            return scatterInfo.attenuation * calculateRayColor(scene, scatterInfo.scatteredRay, depth - 1);
        }

        return {0.0f, 0.0f, 0.0f};
    }

    float t = 0.5f * (glm::normalize(ray.getDirection()).y + 1.0f);
    return (1.0f - t) * glm::vec3(1.0f, 1.0f, 1.0f) + t * glm::vec3(0.5f, 0.7f, 1.0f);
}

void putPixelInArray(uint32_t x, uint32_t y, uint8_t *pixels, glm::vec3 rgb) {
    rgb = glm::sqrt(rgb);
    rgb = glm::clamp(rgb, 0.0f, 1.0f);
    rgb *= 0xFF;

    uint64_t index = (y * WIDTH + x) * 3;
    pixels[index] = static_cast<uint8_t>(rgb.r);
    pixels[index + 1] = static_cast<uint8_t>(rgb.g);
    pixels[index + 2] = static_cast<uint8_t>(rgb.b);
}
