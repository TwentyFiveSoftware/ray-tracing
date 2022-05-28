#pragma once

#include <glm/glm.hpp>
#include "ray.h"
#include "scene.h"
#include "camera.h"

glm::vec3 calculateRayColor(const Scene &scene, const Ray &ray, int32_t depth);

void putPixelInArray(uint32_t x, uint32_t y, uint8_t *pixels, glm::vec3 rgb);

void renderThread(std::atomic<uint32_t> &nextRow, uint8_t *pixels, const Camera &camera, const Scene &scene);
