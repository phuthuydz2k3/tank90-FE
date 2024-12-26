//
// Created by TCT on 12/26/2024.
//

#include "ClickableSystem.h"

#include "ECS/Entity/EntityManager.h"
#include "Game/Common/Event.h"
#include "Game/Components/Transform.h"
#include "Game/UIs/Clickable.h"

void ClickableSystem::update() {
    System::update();
    auto entities = EntityManager::getInstance()->getEntitiesWithComponent<Clickable>();
    for (auto entity : entities) {
        auto clickable = entity->getComponent<Clickable>();
        if (clickable->onClick != nullptr) {
            if(Event::event.type == SDL_MOUSEBUTTONDOWN){
                int x, y;
                SDL_GetMouseState(&x, &y);
                if(!entity->hasComponent<Transform>()) continue;
                Transform* transform = entity->getComponent<Transform>();
                if(x >= (transform->position.x - clickable->size.x / 2) && x <= (transform->position.x + clickable->size.x / 2) &&
                   y >= (transform->position.y - clickable->size.y / 2) && y <= (transform->position.y + clickable->size.y / 2)){
                    clickable->onClick();
                }
            }
        }
    }
}
