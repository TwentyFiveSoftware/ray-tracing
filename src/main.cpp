#include <SDL.h>
#include <thread>
#include <array>
#include "pixel.h"
#include "settings.h"
#include "renderer.h"

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


std::array<std::thread, Settings::RENDER_THREAD_COUNT> renderThreads;
std::array<Pixel, Settings::WIDTH * Settings::HEIGHT> pixels;


void renderPixelsToScreen() {
    for (const Pixel &pixel : pixels) {
        glm::vec3 color = pixel.color * 255.0f;
        SDL_SetRenderDrawColor(renderer, static_cast<uint8_t>(color.x), static_cast<uint8_t>(color.y),
                               static_cast<uint8_t>(color.z), 255);
        SDL_RenderDrawPoint(renderer, pixel.pos.x, pixel.pos.y);
    }
}

int WinMain() {
    initSDL();

    auto rowsPerThread = static_cast<uint16_t>(ceil(float(Settings::HEIGHT) / Settings::RENDER_THREAD_COUNT));
    for (int i = 0; i < Settings::RENDER_THREAD_COUNT; i++) {
        auto startY = static_cast<uint16_t>(std::fmin(i * rowsPerThread, Settings::HEIGHT));
        auto endY = static_cast<uint16_t>(std::fmin(i * rowsPerThread + rowsPerThread, Settings::HEIGHT));
        renderThreads[i] = std::thread(renderThreadEntryPoint, startY, endY, &pixels);
    }

    bool shouldClose = false;

    while (!shouldClose) {
        shouldClose = handleInput();

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        renderPixelsToScreen();

        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / Settings::FPS);
    }


    for (std::thread &renderThread : renderThreads) {
        renderThread.join();
    }

    cleanup();

    return 0;
}
