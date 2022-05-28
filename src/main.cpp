#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <stb_image_write.h>
#include <iostream>
#include <iomanip>
#include <atomic>
#include <thread>
#include "constants.h"
#include "renderer.h"
#include "camera.h"

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

    std::atomic<uint32_t> nextRow = {0};
    std::vector<std::thread> threadPool = {};

    for (int i = 0; i < RENDER_THREADS; ++i) {
        threadPool.emplace_back(std::thread(renderThread, std::ref(nextRow), pixels, camera, scene));
    }

    for (std::thread &thread: threadPool) {
        thread.join();
    }

    stbi_write_png("render.png", WIDTH, HEIGHT, 3, pixels, WIDTH * 3);

    delete[] (pixels);
    return 0;
}
