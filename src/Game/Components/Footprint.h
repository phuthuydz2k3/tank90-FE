//
// Created by TCT on 12/27/2024.
//

#ifndef FOOTPRINT_H
#define FOOTPRINT_H
#include <SDL_render.h>

#include "ECS/Component/Component.h"


class Footprint : public Component {
public:
    float countTime = 0.0f;
    float time = 0.05f;
};


#endif //FOOTPRINT_H
