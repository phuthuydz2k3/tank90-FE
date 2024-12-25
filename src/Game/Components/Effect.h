//
// Created by TCT on 11/23/2024.
//

#ifndef EFFECT_H
#define EFFECT_H
#include <functional>
#include <list>
#include <SDL_render.h>

#include "ECS/Component/Component.h"
#include "Math/Vector2.h"

struct Frame {
    SDL_Texture *texture;
    SDL_Rect *srcRect = nullptr;
};


class Effect : public Component {
public:
    Effect();

    Effect(const VECTOR2 &size, float timePerFrame);

    int currentFrame = 0;
    float timeCount = 0.0f;
    std::list<Frame> frames;
    VECTOR2 size;
    float timePerFrame;
    int loop;
    int currentLoop = 1;

    std::function<void()> onEnd;
};


#endif //EFFECT_H
