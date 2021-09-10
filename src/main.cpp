#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <SDL.h>
#include <stb_image_write.h>
#include <thread>
#include <array>
#include <iostream>
#include "settings/settings.h"
#include "objects/sphere.h"
#include "objects/hittable_list.h"
#include "renderer.h"
#include "material/material.h"
#include "material/material_diffuse.h"
#include "material/material_metal.h"

SDL_Window* window;
SDL_Renderer* renderer;

void initSDL() {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Ray Tracing", 100, 100, Settings::WIDTH, Settings::HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, 0);
}

bool handleInput() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                return true;

            default:
                break;
        }
    }

    return false;
}

void cleanup() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


unsigned char* pixels = new unsigned char[Settings::WIDTH * Settings::HEIGHT * 3];
std::atomic<uint32_t> pixelsRendered = {0};

void renderPixelsToScreen() {
    for (uint16_t y = 0; y < Settings::HEIGHT; y++) {
        for (uint16_t x = 0; x < Settings::WIDTH; x++) {
            int index = (y * Settings::WIDTH + x) * 3;

            SDL_SetRenderDrawColor(renderer, pixels[index + 0], pixels[index + 1], pixels[index + 2], 0xFF);
            SDL_RenderDrawPoint(renderer, x, y);
        }
    }
}

void saveImage() {
    stbi_write_png("render.png", Settings::WIDTH, Settings::HEIGHT, 3, pixels, Settings::WIDTH * 3);
}


std::array<std::thread, Settings::RENDER_THREAD_COUNT> renderThreads;
std::atomic<uint16_t> nextPixelRowToRender = {0};

int WinMain() {
    // INIT
    initSDL();

    for (int i = 0; i < Settings::WIDTH * Settings::HEIGHT * 3; i++) {
        pixels[i] = 0x00;
    }

    // MATERIALS
    auto materialGround = std::make_shared<MaterialDiffuse>(glm::vec3(0.8f, 0.8f, 0.0f));
    auto materialCenter = std::make_shared<MaterialDiffuse>(glm::vec3(0.7f, 0.3f, 0.3f));
    auto materialLeft = std::make_shared<MaterialMetal>(glm::vec3(0.8f, 0.8f, 0.8f));
    auto materialRight = std::make_shared<MaterialMetal>(glm::vec3(0.8f, 0.6f, 0.2f));

    // WORLD
    HittableList world;
    world.add(std::make_shared<Sphere>(glm::vec3(0.0f, -100.5f, 1.0f), 100.0f, materialGround));
    world.add(std::make_shared<Sphere>(glm::vec3(0.0f, 0.0f, 1.0f), 0.5f, materialCenter));
    world.add(std::make_shared<Sphere>(glm::vec3(-1.25f, 0.0f, 1.0f), 0.5f, materialLeft));
    world.add(std::make_shared<Sphere>(glm::vec3(1.0f, 0.5f, 1.0f), 0.3f, materialRight));

    // CAMERA
    Camera camera;

    // RENDER THREADS
    auto renderBeginTime = std::chrono::steady_clock::now();
    std::optional<std::chrono::steady_clock::time_point> renderEndTime = std::nullopt;

    ThreadInfo threadInfo = {
            .pixels = pixels,
            .nextPixelRowToRender = &nextPixelRowToRender,
            .pixelsRendered = &pixelsRendered,
            .world = world,
            .camera = camera
    };

    for (int i = 0; i < Settings::RENDER_THREAD_COUNT; i++) {
        renderThreads[i] = std::thread(renderThreadFunction, threadInfo);
    }

    // DISPLAY
    bool shouldClose = false;

    while (!shouldClose) {
        shouldClose = handleInput();

        if (!renderEndTime) {
            if (pixelsRendered == Settings::WIDTH * Settings::HEIGHT) {
                renderEndTime = std::chrono::steady_clock::now();
                std::cout << "Rendered in "
                          << std::chrono::duration_cast<std::chrono::milliseconds>(
                                  renderEndTime.value() - renderBeginTime).count()
                          << "ms" << std::endl;

                saveImage();
            }


            renderPixelsToScreen();

            SDL_RenderPresent(renderer);
        }

        SDL_Delay(1000 / Settings::FPS);
    }

    // CLEANUP
    nextPixelRowToRender = Settings::HEIGHT;

    for (std::thread &renderThread : renderThreads) {
        renderThread.join();
    }

    delete[] pixels;

    cleanup();

    return 0;
}
