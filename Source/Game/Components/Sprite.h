//
// Created by TCT on 10/31/2024.
//

#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H
#include <SDL_render.h>
#include <string>

#include "ECS/Component/Component.h"
#include "Math/Vector2.h"


class Sprite : public Component {
public:
    Sprite();

    Sprite(const std::string &pathSprite, const VECTOR2 &size, SDL_Rect *srcRect, int layer);

    SDL_Texture *texture;
    VECTOR2 size;
    SDL_Rect *srcRect;
    int layer;
};


#endif //SPRITECOMPONENT_H
