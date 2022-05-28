#include <iostream>
#include <atomic>
#include "renderer.h"
#include "constants.h"
#include "hit_record.h"
#include "scatter.h"
#include "utils.h"

HitRecord rayHitsScene(const Scene &scene, const Ray &ray, float tMin, float tMax) {
    HitRecord currentHitRecord = {.t = tMax};

    for (const Sphere &sphere: *scene.getSpheres()) {
        HitRecord hitRecord = sphere.rayHitsSphere(ray, tMin, currentHitRecord.t);
        if (hitRecord.hit) {
            currentHitRecord = hitRecord;
        }
    }

    return currentHitRecord;
}

//glm::vec3 calculateRayColor(const Scene &scene, const Ray &ray, int32_t depth) {
//    if (depth <= 0) {
//        return {0.0f, 0.0f, 0.0f};
//    }
//
//    HitRecord hitRecord = rayHitsScene(scene, ray, 0.001f, std::numeric_limits<float>::infinity());
//    if (hitRecord.hit) {
//        ScatterInfo scatterInfo = scatter(ray, hitRecord);
//
//        if (scatterInfo.doesScatter) {
//            return scatterInfo.attenuation * calculateRayColor(scene, scatterInfo.scatteredRay, depth - 1);
//        }
//
//        return {0.0f, 0.0f, 0.0f};
//    }
//
//    float t = 0.5f * (ray.direction.y + 1.0f);
//    return (1.0f - t) * glm::vec3(1.0f, 1.0f, 1.0f) + t * glm::vec3(0.5f, 0.7f, 1.0f);
//}

glm::vec3 calculateRayColor(const Scene &scene, const Ray &cameraRay) {
    glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 lightSourceColor = glm::vec3(0.0f, 0.0f, 0.0f);
    Ray ray = cameraRay;

    for (uint32_t depth = 0; depth < MAX_RAY_TRACE_DEPTH; depth++) {
        HitRecord hitRecord = rayHitsScene(scene, ray, 0.001f, std::numeric_limits<float>::infinity());

        if (!hitRecord.hit) {
            lightSourceColor = glm::vec3(0.7f, 0.8f, 1.0f);
            break;
        }

        ScatterInfo scatterInfo = scatter(ray, hitRecord);
        if (scatterInfo.doesScatter) {
            color *= scatterInfo.attenuation;
            ray = scatterInfo.scatteredRay;
        } else {
            lightSourceColor = glm::vec3(0.0f, 0.0f, 0.0f);
            break;
        }
    }

    return color * lightSourceColor;
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

void renderRow(uint32_t y, uint8_t *pixels, const Camera &camera, const Scene &scene) {
    for (uint32_t x = 0; x < WIDTH; ++x) {
        glm::vec3 pixelColor = glm::vec3(0.0f, 0.0f, 0.0f);

        for (uint32_t sample = 0; sample < SAMPLES_PER_PIXEL; ++sample) {
            float u = (float(x) + randomFloat()) / (WIDTH - 1);
            float v = (float(y) + randomFloat()) / (HEIGHT - 1);

            Ray ray = camera.getRay(u, v);
            pixelColor += calculateRayColor(scene, ray);
//            pixelColor += calculateRayColor(scene, ray, MAX_RAY_TRACE_DEPTH);
        }

        pixelColor /= float(SAMPLES_PER_PIXEL);
        putPixelInArray(x, y, pixels, pixelColor);
    }
}

void renderThread(std::atomic<uint32_t> &nextRow, uint8_t *pixels, const Camera &camera, const Scene &scene) {
    while (true) {
        uint32_t y = nextRow++;

        if (y >= HEIGHT) {
            return;
        }

        std::cout << (y + 1) << " / " << HEIGHT << " (" << (float(y + 1) / HEIGHT * 100.0f) << "%)" << std::endl;
        renderRow(y, pixels, camera, scene);
    }
}
