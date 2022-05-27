#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <stb_image_write.h>
#include <iostream>
#include <iomanip>
#include "constants.h"
#include "renderer.h"
#include "camera.h"
#include "utils.h"

int main(int argc, char *argv[]) {
    std::cout << std::fixed;
    std::cout << std::setprecision(2);

    auto camera = Camera(
            glm::vec3(12.0f, 2.0f, -3.0f),
            glm::vec3(0.0, 0.0, 0.0),
            25.0,
            0.0,
            10.0
    );

    auto scene = Scene();

    auto *pixels = new uint8_t[WIDTH * HEIGHT * 3];

    for (uint32_t y = 0; y < HEIGHT; ++y) {
        std::cout << (y + 1) << " / " << HEIGHT << " (" << (float(y + 1) / HEIGHT * 100.0f) << "%)" << std::endl;

        for (uint32_t x = 0; x < WIDTH; ++x) {
            glm::vec3 pixelColor = glm::vec3(0.0f, 0.0f, 0.0f);

            for (uint32_t sample = 0; sample < SAMPLES_PER_PIXEL; ++sample) {
                float u = (float(x) + randomFloat()) / (WIDTH - 1);
                float v = (float(y) + randomFloat()) / (HEIGHT - 1);

                Ray ray = camera.getRay(u, v);
                pixelColor += calculateRayColor(scene, ray, MAX_RAY_TRACE_DEPTH);
            }

            pixelColor /= float(SAMPLES_PER_PIXEL);
            putPixelInArray(x, y, pixels, pixelColor);
        }
    }

    stbi_write_png("render.png", WIDTH, HEIGHT, 3, pixels, WIDTH * 3);

    delete[] (pixels);
    return 0;
}

