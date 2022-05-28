#pragma once

#include <glm/glm.hpp>
#include "ray.h"
#include "scene.h"
#include "camera.h"

void renderThread(std::atomic<uint32_t> &nextRow, uint8_t *pixels, const Camera &camera, const Scene &scene);
