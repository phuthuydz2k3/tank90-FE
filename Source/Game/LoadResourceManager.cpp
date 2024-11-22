//
// Created by TCT on 10/31/2024.
//

#include "LoadResourceManager.h"

const float WINDOW_WIDTH = 800;
const float WINDOW_HEIGHT = 600;

SDL_Texture *LoadResourceManager::LoadTexture(const std::string &path) const {
    SDL_Texture *texturePtr = IMG_LoadTexture(this->renderer, path.c_str());
    if (!texturePtr) {
        SDL_DestroyTexture(texturePtr);
        std::cerr << "Path is not correct" << SDL_GetError() << std::endl;
    }
    return texturePtr;
}

void LoadResourceManager::InitWindow() {
    this->window = SDL_CreateWindow("Tank Game",
                                    SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED,
                                    WINDOW_WIDTH, WINDOW_HEIGHT,
                                    SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window haven't been initialized: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }
    this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer haven't been initialized: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }
}

void LoadResourceManager::CleanUp() const {
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

SDL_Window *LoadResourceManager::GetWindow() const {
    return this->window;
}

SDL_Renderer *LoadResourceManager::GetRenderer() const {
    return this->renderer;
}
