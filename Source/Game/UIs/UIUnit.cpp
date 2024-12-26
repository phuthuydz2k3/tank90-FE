//
// Created by TCT on 12/26/2024.
//

#include "UIUnit.h"

#include "ECS/Entity/EntityManager.h"

void UIUnit::Init() {
}

void UIUnit::Close() {
    for (auto idEntity: idEntities) {
        EntityManager::getInstance()->removeEntity(idEntity);
    }
}
