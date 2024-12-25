//
// Created by TCT on 11/22/2024.
//

#ifndef CONTROLSYSTEM_H
#define CONTROLSYSTEM_H
#include "ECS/System/System.h"


class ControlSystem : public System {
    void update() override;
    void init() override;

};



#endif //CONTROLSYSTEM_H
