//
// Created by TCT on 11/23/2024.
//

#ifndef FLYSYSTEM_H
#define FLYSYSTEM_H
#include "ECS/System/System.h"
#include "Game/Common/Time.h"
#include "Game/Components/FlyComponent.h"
#include "Game/Components/Transform.h"
#include "ECS/Entity/EntityManager.h"



class FlySystem : public System {
    void update() override;
};


#endif //FLYSYSTEM_H
