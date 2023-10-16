#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <stb_image_write.h>
#include <iostream>
#include <iomanip>
#include <atomic>
#include <thread>
#include "constants.h"
#include "renderer.h"
#include "camera.h"

int main() {
    std::cout << std::fixed;
    std::cout << std::setprecision(2);

    auto camera = Camera(
            vec3(12.0f, 2.0f, -3.0f),
            vec3(0.0, 0.0, 0.0),
            25.0,
            0.0,
            10.0
    );

    auto scene = Scene();

    auto *pixels = new uint8_t[WIDTH * HEIGHT * 3];

    std::atomic<uint32_t> nextRow = {0};
    std::vector<std::thread> threadPool = {};

    auto renderStartTime = std::chrono::steady_clock::now();

    for (int i = 0; i < RENDER_THREADS; ++i) {
        threadPool.emplace_back(std::thread(renderThread, std::ref(nextRow), pixels, camera, scene));
    }

    for (std::thread &thread: threadPool) {
        thread.join();
    }

    auto elapsedRenderTime = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now() - renderStartTime).count();
    std::cout << "rendered " << SAMPLES_PER_PIXEL << " samples/pixel with " << RENDER_THREADS << " threads in "
              << elapsedRenderTime << " ms" << std::endl;

    stbi_write_png("render.png", WIDTH, HEIGHT, 3, pixels, WIDTH * 3);

    delete[] (pixels);
    return 0;
}
