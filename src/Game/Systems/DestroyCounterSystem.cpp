//
// Created by TCT on 11/23/2024.
//

#include "DestroyCounterSystem.h"

#include "ECS/Entity/EntityManager.h"
#include "Game/Common/Time.h"
#include "Game/Components/DestroyCounter.h"

void DestroyCounterSystem::update() {
    System::update();
    auto entities = EntityManager::getInstance()->getEntitiesWithComponent<DestroyCounter>();
    for (auto &entity: entities) {
        DestroyCounter *destroyCounter = entity->getComponent<DestroyCounter>();
        destroyCounter->countTime += Time::deltaTime;
        if (destroyCounter->countTime < destroyCounter->timeCounter) continue;
        EntityManager::getInstance()->removeEntity(entity->getId());
    }
}
