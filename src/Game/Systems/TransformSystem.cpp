//
// Created by TCT on 12/27/2024.
//

#include "TransformSystem.h"

#include "ECS/Entity/EntityManager.h"
#include "Game/Components/Transform.h"

void TransformSystem::update() {
    System::update();
    auto entities = EntityManager::getInstance()->getEntitiesWithComponent<Transform>();
    for (auto entity: entities) {
        auto transform = entity->getComponent<Transform>();
        if (transform->parent == nullptr) continue;
        transform->angle = transform->parent->angle + transform->localAngle;
        transform->position = transform->parent->position + transform->localPosition.rotate(transform->parent->angle);
    }
}
