//
// Created by TCT on 11/23/2024.
//

#ifndef BULLET_H
#define BULLET_H
#include "ECS/Entity/Entity.h"

#include "Game/LoadResourceManager.h"
#include "Game/Components/Sprite.h"
#include "Game/Components/Transform.h"
#include "Game/Components/FlyComponent.h"


class Bullet : public Entity {
public:
    Bullet();
};


#endif //BULLET_H
