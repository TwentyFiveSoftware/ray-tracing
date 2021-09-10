#pragma once

#include <array>
#include <atomic>
#include "settings/settings.h"
#include "objects/hittable_list.h"
#include "camera.h"

void renderThreadEntryPoint(std::atomic<uint16_t>* nextPixelRowToRender, unsigned char* pixels,
                            std::atomic<uint32_t>* pixelsRendered, const HittableList &world, const Camera &camera);
