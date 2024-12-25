//
// Created by TCT on 12/26/2024.
//

#include "BeDestroy.h"

#include "ECS/Entity/Entity.h"
#include "ECS/Entity/EntityManager.h"

void BeDestroy::Destroy() {
    EntityManager::getInstance()->removeEntity(static_cast<Entity*>(this->owner)->getId());
}
