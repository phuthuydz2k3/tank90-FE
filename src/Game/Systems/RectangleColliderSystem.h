//
// Created by TCT on 11/23/2024.
//

#ifndef RECTANGLECOLLIDERSYSTEM_H
#define RECTANGLECOLLIDERSYSTEM_H
#include "ECS/System/System.h"


class RectangleColliderSystem : public System{
    void update() override;
    void init() override;

};



#endif //RECTANGLECOLLIDERSYSTEM_H
