#include <SDL2/SDL.h>
#include <iostream>
#include <cstring>
#include <SDL2/SDL_net.h>

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


    // Initialize SDL_net
    if (SDLNet_Init() < 0) {
        std::cerr << "SDL_net haven't been initialized: " << SDLNet_GetError() << std::endl;
        SDL_Quit();
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
        SDLNet_Quit();
        SDL_Quit();
        return 1;
    }

    // Renderer Initialization
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer haven't been initialized: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDLNet_Quit();
        SDL_Quit();
        return 1;
    }

    // Network setup
    IPaddress ip;
    if (SDLNet_ResolveHost(&ip, "127.0.0.1", 12345) < 0) {
        std::cerr << "Failed to resolve host: " << SDLNet_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDLNet_Quit();
        SDL_Quit();
        return 1;
    }

    UDPsocket socket = SDLNet_UDP_Open(0);
    if (!socket) {
        std::cerr << "Failed to open UDP socket: " << SDLNet_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDLNet_Quit();
        SDL_Quit();
        return 1;
    }

    UDPpacket *packet = SDLNet_AllocPacket(512);
    if (!packet) {
        std::cerr << "Failed to allocate packet: " << SDLNet_GetError() << std::endl;
        SDLNet_UDP_Close(socket);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDLNet_Quit();
        SDL_Quit();
        return 1;
    }

    packet->address = ip;

    // Game loop
    bool running = true;
    SDL_Event event;
    Uint32 lastTime = SDL_GetTicks();
    Uint32 lastSendTime = SDL_GetTicks();
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

        // Send 50 frames every second
        // 1000ms / 50 = 20ms
        if (currentTime - lastSendTime >= 20) {
            lastSendTime = currentTime;
            std::string posStr = std::to_string(squarePos.x) + "," + std::to_string(squarePos.y);
            std::strcpy((char *)packet->data, posStr.c_str());
            packet->len = posStr.length() + 1;
            SDLNet_UDP_Send(socket, -1, packet);
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
    SDLNet_FreePacket(packet);
    SDLNet_UDP_Close(socket);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDLNet_Quit();
    SDL_Quit();

    return 0;
}
