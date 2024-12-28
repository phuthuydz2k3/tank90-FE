//
// Created by TCT on 12/27/2024.
//

#include "FootprintSystem.h"

#include "ECS/Entity/EntityManager.h"
#include "Game/Common/Time.h"
#include "Game/Components/DestroyCounter.h"
#include "Game/Components/Footprint.h"
#include "Game/Components/Sprite.h"
#include "Game/Components/Transform.h"
#include "Game/Entities/GameObject.h"
#include "Game/Manager/LoadResourceManager.h"

void FootprintSystem::update() {
    System::update();
    auto entities = EntityManager::getInstance()->getEntitiesWithComponent<Footprint>();
    for (auto &entity: entities) {
        Transform *transform = entity->getComponent<Transform>();
        Footprint *footprint = entity->getComponent<Footprint>();
        Sprite *sprite = entity->getComponent<Sprite>();
        footprint->countTime += Time::deltaTime;
        if (footprint->countTime < footprint->time) continue;
        footprint->countTime = 0;
        GameObject *footprintObject = EntityManager::getInstance()->createEntity<GameObject>();
        footprintObject->addComponent<Transform>();
        footprintObject->addComponent<Sprite>();
        footprintObject->addComponent<DestroyCounter>();

        footprintObject->getComponent<Transform>()->position =
                transform->position - transform->forward() * sprite->size.y / 2;
        footprintObject->getComponent<Transform>()->angle = transform->angle;
        footprintObject->getComponent<Sprite>()->texture = LoadResourceManager::getInstance()->LoadTexture(
            "../Data/Images/tracksSmall.png");
        footprintObject->getComponent<Sprite>()->srcRect = new SDL_Rect({0, 0, 74, 15});
        footprintObject->getComponent<Sprite>()->size = {sprite->size.y, sprite->size.y / 74 * 15};
        footprintObject->getComponent<Sprite>()->layer = -1;
        footprintObject->getComponent<DestroyCounter>()->timeCounter = 2.0f;
    }
}
