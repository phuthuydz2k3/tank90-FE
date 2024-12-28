//
// Created by TCT on 11/23/2024.
//

#include "FlySystem.h"



void FlySystem::update() {
    System::update();
    auto entities = EntityManager::getInstance()->getEntitiesWithComponent<FlyComponent>();
    for (auto &entity: entities) {
        FlyComponent *fly = entity->getComponent<FlyComponent>();
        Transform *transform = entity->getComponent<Transform>();
        transform->position += transform->forward() * Time::deltaTime * fly->speed;
    }
}
