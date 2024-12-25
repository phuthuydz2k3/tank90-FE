//
// Created by TCT on 10/31/2024.
//

#include "LoadResourceManager.h"

const float WINDOW_WIDTH = 800;
const float WINDOW_HEIGHT = 800;

SDL_Texture *LoadResourceManager::LoadTexture(const std::string &path) {
    if (this->cacheTexture.find(path) != this->cacheTexture.end()) {
        return this->cacheTexture.at(path);
    }
    SDL_Texture *texturePtr = IMG_LoadTexture(this->renderer, path.c_str());
    if (!texturePtr) {
        SDL_DestroyTexture(texturePtr);
        std::cerr << "Path is not correct" << SDL_GetError() << std::endl;
    }
    this->cacheTexture[path] = texturePtr;
    return texturePtr;
}

Mix_Chunk *LoadResourceManager::LoadSound(const std::string &path) {
    if (this->cacheSound.find(path) != this->cacheSound.end()) {
        return this->cacheSound.at(path);
    }
    Mix_Chunk *sound = Mix_LoadWAV(path.c_str());
    if (!sound) {
        Mix_FreeChunk(sound);
        Mix_CloseAudio();
        Mix_Quit();
        std::cerr << "Path is not correct" << Mix_GetError() << std::endl;
        return nullptr;
    }
    this->cacheSound[path] = sound;
    return sound;
}

void LoadResourceManager::InitWindow() {
    this->window = SDL_CreateWindow("Tank Game",
                                    SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED,
                                    WINDOW_WIDTH, WINDOW_HEIGHT,
                                    SDL_WINDOW_SHOWN);
    if (!this->window) {
        std::cerr << "Window haven't been initialized: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer haven't been initialized: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(this->window);
        SDL_Quit();
        return;
    }
    SDL_SetWindowResizable(this->window, SDL_FALSE);
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
