#pragma once

#include <glm/glm.hpp>
#include "ray.h"
#include "scene.h"

glm::vec3 calculateRayColor(const Scene &scene, const Ray &ray);

void putPixelInArray(uint32_t x, uint32_t y, uint8_t *pixels, glm::vec3 rgb);
