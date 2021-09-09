#include <SDL.h>
#include <thread>
#include <glm/glm.hpp>
//#include <chrono>

SDL_Window* window;
SDL_Renderer* renderer;

const uint16_t FPS = 10;
const uint16_t RENDER_THREAD_COUNT = 4;
const uint16_t WIDTH = 1000;
const uint16_t HEIGHT = 600;


void initSDL() {
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("Ray Tracing", 100, 100, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

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


struct Pixel {
    glm::ivec2 pos;
    glm::vec3 color;
};

Pixel pixels[WIDTH * HEIGHT];


void render(uint16_t startY, uint16_t endY) {
    for (uint16_t y = startY; y < endY; y++) {
        for (uint16_t x = 0; x < WIDTH; x++) {
            float r = float(x) / WIDTH;
            float g = float(y) / HEIGHT;
            float b = 0.25f;

            pixels[y * WIDTH + x] = {
                    .pos = {x, y},
                    .color = {r, g, b}
            };
        }

//        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}


void renderPixelsToScreen() {
    for (const Pixel &pixel : pixels) {
        glm::vec3 color = pixel.color * 255.0f;
        SDL_SetRenderDrawColor(renderer, static_cast<uint8_t>(color.x), static_cast<uint8_t>(color.y),
                               static_cast<uint8_t>(color.z), 255);
        SDL_RenderDrawPoint(renderer, pixel.pos.x, pixel.pos.y);
    }
}

std::thread renderThreads[RENDER_THREAD_COUNT];

int WinMain() {
    initSDL();

    auto rowsPerThread = static_cast<uint16_t>(ceil(float(HEIGHT) / RENDER_THREAD_COUNT));
    for (int i = 0; i < RENDER_THREAD_COUNT; i++) {
        uint16_t startY = static_cast<uint16_t>(std::fmin(i * rowsPerThread, HEIGHT));
        uint16_t endY = static_cast<uint16_t>(std::fmin(i * rowsPerThread + rowsPerThread, HEIGHT));
        renderThreads[i] = std::thread(render, startY, endY);
    }

    bool shouldClose = false;

    while (!shouldClose) {
        shouldClose = handleInput();

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        renderPixelsToScreen();

        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / FPS);
    }


    for (std::thread &renderThread : renderThreads) {
        renderThread.join();
    }

    cleanup();

    return 0;
}
