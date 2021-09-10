#pragma once

#include <array>
#include <atomic>
#include "structs/pixel.h"
#include "settings/settings.h"
#include "objects/hittable_list.h"
#include "camera.h"

void renderThreadEntryPoint(uint16_t startY, uint16_t endY,
                            std::array<Pixel, Settings::WIDTH * Settings::HEIGHT>* pixels,
                            std::atomic<uint32_t>* pixelsRendered,
                            const HittableList &world,
                            const Camera &camera);
