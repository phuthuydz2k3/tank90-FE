//
// Created by TCT on 11/22/2024.
//

#ifndef SPRITESYSTEM_H
#define SPRITESYSTEM_H
#include "ECS/System/System.h"


class SpriteSystem : public System{
    void update() override;
    void init() override;
};



#endif //SPRITESYSTEM_H
