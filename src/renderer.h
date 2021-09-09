#pragma once

#include <array>
#include <atomic>
#include "pixel.h"
#include "settings.h"

void renderThreadEntryPoint(uint16_t startY, uint16_t endY,
                            std::array<Pixel, Settings::WIDTH * Settings::HEIGHT>* pixels,
                            std::atomic<uint32_t>* pixelsRendered);
