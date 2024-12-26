//
// Created by TCT on 12/26/2024.
//

#include "BeDestroy.h"

#include <iostream>

#include "ECS/Entity/Entity.h"
#include "ECS/Entity/EntityManager.h"
#include "Game/Components/ControlComponent.h"
#include "Game/Components/RectangleCollider.h"
#include "Game/Manager/UIManager.h"
#include "Game/Services/GameplayService.h"
#include "Game/UIs/WinUI.h"

void BeDestroy::Destroy() {
    if (static_cast<Entity *>(this->owner)->hasComponent<ControlComponent>()) {
        GameplayService().LoseGame();
    }
    if (static_cast<Entity *>(this->owner)->getComponent<RectangleCollider>()->layer == Enemy) {
        auto entities = EntityManager::getInstance()->getEntitiesWithComponent<BeDestroy>();
        if (entities.size() == 2) {
            GameplayService().WinGame();
        }
    }
    EntityManager::getInstance()->removeEntity(static_cast<Entity *>(this->owner)->getId());
}
