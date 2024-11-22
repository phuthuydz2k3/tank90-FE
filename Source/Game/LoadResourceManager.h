//
// Created by TCT on 10/31/2024.
//

#ifndef LOADRESOURCEMANAGER_H
#define LOADRESOURCEMANAGER_H
#include <SDL_render.h>
#include <string>
#include "SingletonTemplate.h"
#include <iostream>
#include <SDL_image.h>


class LoadResourceManager : public SingletonTemplate<LoadResourceManager> {
public:
    SDL_Texture *LoadTexture(const std::string &) const;

    void InitWindow();
    void CleanUp() const;

    SDL_Window *GetWindow() const;
    SDL_Renderer *GetRenderer() const;

private:
    SDL_Renderer *renderer;
    SDL_Window *window;
};


#endif //LOADRESOURCEMANAGER_H
