//
// Created by TCT on 12/27/2024.
//

#include "CursorSystem.h"

#include <SDL_mouse.h>

#include "ECS/Entity/EntityManager.h"
#include "Game/Components/Cursor.h"
#include "Game/Components/Transform.h"

void CursorSystem::update() {
    System::update();
    auto entities = EntityManager::getInstance()->getEntitiesWithComponent<Cursor>();
    for (auto entity: entities) {
        Transform *transform = entity->getComponent<Transform>();
        int x, y;
        SDL_GetMouseState(&x, &y);
        transform->position = VECTOR2(x, y);
    }
}
