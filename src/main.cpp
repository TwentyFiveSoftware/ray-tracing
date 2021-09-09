#include <SDL.h>

SDL_Window* window;
SDL_Renderer* renderer;

const int16_t FPS = 10;

void initSDL() {
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("Ray Tracing", 100, 100,
                              1000, 600, SDL_WINDOW_SHOWN);

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

int WinMain() {
    initSDL();

    bool shouldClose = false;

    while (!shouldClose) {
        shouldClose = handleInput();

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderDrawPoint(renderer, 100, 100);

        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / FPS);
    }

    cleanup();

    return 0;
}
