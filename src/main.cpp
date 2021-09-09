#include <SDL.h>

SDL_Window* window;
SDL_Renderer* renderer;

const uint16_t FPS = 10;
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
    uint16_t x, y;
    uint16_t r, g, b;
};

Pixel pixels[WIDTH * HEIGHT];


void render() {
    for (uint16_t y = 0; y < HEIGHT; ++y) {
        for (uint16_t x = 0; x < WIDTH; ++x) {
            auto r = static_cast<uint16_t>((float(x) / WIDTH) * 255);
            auto g = static_cast<uint16_t>((float(y) / HEIGHT) * 255);
            uint16_t b = 64;

            pixels[y * WIDTH + x] = {x, y, r, g, b};
        }
    }
}


void renderPixelsToScreen() {
    for (Pixel pixel : pixels) {
        SDL_SetRenderDrawColor(renderer, pixel.r, pixel.g, pixel.b, 255);
        SDL_RenderDrawPoint(renderer, pixel.x, pixel.y);
    }
}

int WinMain() {
    initSDL();

    render();

    bool shouldClose = false;

    while (!shouldClose) {
        shouldClose = handleInput();

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        renderPixelsToScreen();

        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / FPS);
    }

    cleanup();

    return 0;
}
