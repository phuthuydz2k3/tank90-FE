//
// Created by TCT on 12/26/2024.
//

#include "ClickableSystem.h"

#include <iostream>

#include "ECS/Entity/EntityManager.h"
#include "Game/Common/Event.h"
#include "Game/Components/Transform.h"
#include "Game/UIs/Clickable.h"

void ClickableSystem::update() {
    System::update();
    while (SDL_PollEvent(&Event::event)) {
        if (Event::event.type == SDL_MOUSEBUTTONUP && Event::event.button.button == SDL_BUTTON_LEFT) {
            auto entities = EntityManager::getInstance()->getEntitiesWithComponent<Clickable>();
            for (auto entity: entities) {
                auto clickable = entity->getComponent<Clickable>();
                int x, y;
                SDL_GetMouseState(&x, &y);
                if (entity->hasComponent<Transform>() && clickable->onClick != nullptr) {
                    Transform *transform = entity->getComponent<Transform>();
                    if (x >= (transform->position.x - clickable->size.x / 2) && x <= (
                            transform->position.x + clickable->size.x / 2) &&
                        y >= (transform->position.y - clickable->size.y / 2) && y <= (
                            transform->position.y + clickable->size.y / 2)) {
                        clickable->onClick();
                    }
                }
            }
        }
    }
}
