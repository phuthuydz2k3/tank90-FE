#include <SDL2/SDL.h>
#include <iostream>
#include "Math/Vector2.h"

// Define window size
const float WINDOW_WIDTH = 800;
const float WINDOW_HEIGHT = 600;

// Define rect size and position
const int SQUARE_SIZE = 50;
VECTOR2 squarePos = VECTOR2(WINDOW_WIDTH / 2 - SQUARE_SIZE / 2, WINDOW_HEIGHT / 2 - SQUARE_SIZE / 2);

// Define move speed
const float MOVE_SPEED = 200.0f; // Pixels per second

int main(int argc, char *argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL haven't been initialized: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create window
    SDL_Window *window = SDL_CreateWindow("Tank Game",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          WINDOW_WIDTH, WINDOW_HEIGHT,
                                          SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window haven't been initialized: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Renderer Initialization
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer haven't been initialized: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Game loop
    bool running = true;
    SDL_Event event;
    Uint32 lastTime = SDL_GetTicks();
    while (running) {
        // Event handling
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f; // Convert milliseconds to seconds
        lastTime = currentTime; // Update last time
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Get the current state of the keyboard
        const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);
        VECTOR2 move = VECTOR2(0, 0);

        if (currentKeyStates[SDL_SCANCODE_UP]) move.y -= 1;
        if (currentKeyStates[SDL_SCANCODE_DOWN]) move.y += 1;
        if (currentKeyStates[SDL_SCANCODE_LEFT]) move.x -= 1;
        if (currentKeyStates[SDL_SCANCODE_RIGHT]) move.x += 1;

        if (move.x != 0 || move.y != 0) {
            move = move.normalize();
            squarePos += move * (MOVE_SPEED * deltaTime);
        }

        // Background color
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw square
        SDL_Rect square = {static_cast<int>(squarePos.x), static_cast<int>(squarePos.y), SQUARE_SIZE, SQUARE_SIZE};
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &square);

        // Update screen
        SDL_RenderPresent(renderer);

        // Delay
        SDL_Delay(16);
    }

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
