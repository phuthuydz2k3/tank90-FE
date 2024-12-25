//
// Created by TCT on 10/31/2024.
//

#ifndef LOADRESOURCEMANAGER_H
#define LOADRESOURCEMANAGER_H
#include <SDL2/SDL_render.h>
#include <string>
#include "../../SingletonTemplate.h"
#include <iostream>
#include <SDL2/SDL_image.h>
#include <unordered_map>
#include <SDL2/SDL_mixer.h>


class LoadResourceManager : public SingletonTemplate<LoadResourceManager> {
public:
    SDL_Texture *LoadTexture(const std::string &);

    Mix_Chunk *LoadSound(const std::string &);

    void InitWindow();

    void CleanUp() const;

    SDL_Window *GetWindow() const;

    SDL_Renderer *GetRenderer() const;

private:
    SDL_Renderer *renderer;
    SDL_Window *window;
    std::unordered_map<std::string, SDL_Texture *> cacheTexture;
    std::unordered_map<std::string, Mix_Chunk *> cacheSound;
};


#endif
