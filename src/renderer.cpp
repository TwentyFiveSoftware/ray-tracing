#include "renderer.h"

void renderThreadEntryPoint(uint16_t startY, uint16_t endY,
                            std::array<Pixel, Settings::WIDTH * Settings::HEIGHT>* pixels) {

    for (uint16_t y = startY; y < endY; y++) {
        for (uint16_t x = 0; x < Settings::WIDTH; x++) {
            float r = float(x) / Settings::WIDTH;
            float g = float(y) / Settings::HEIGHT;
            float b = 0.25f;

            Pixel pixel = {
                    .pos = {x, y},
                    .color = {r, g, b}
            };

            pixels->at(y * Settings::WIDTH + x) = pixel;
        }
    }
}
