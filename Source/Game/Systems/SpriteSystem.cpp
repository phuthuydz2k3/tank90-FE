//
// Created by TCT on 11/22/2024.
//

#include "SpriteSystem.h"

#include "ECS/Entity/EntityManager.h"
#include "Game/LoadResourceManager.h"
#include "Game/Components/Sprite.h"
#include "Game/Components/Transform.h"

class Transform;
class Sprite;


void SpriteSystem::update() {
    System::update();
    SDL_RenderClear(LoadResourceManager::getInstance()->GetRenderer());
    auto entities = EntityManager::getInstance()->getEntitiesWithComponent<Sprite>();
    for (auto &entity: entities) {
        Sprite *sprite = entity->getComponent<Sprite>();
        if (sprite->texture == nullptr) continue;
        Transform *transform = entity->getComponent<Transform>();
        SDL_Rect dstRect = {
            static_cast<int>(transform->position.x - sprite->size.x * transform->scale.x / 2),
            static_cast<int>(transform->position.y - sprite->size.y * transform->scale.y / 2),
            static_cast<int>(sprite->size.x * transform->scale.x),
            static_cast<int>(sprite->size.y * transform->scale.y)
        };
        SDL_RenderCopyEx(LoadResourceManager::getInstance()->GetRenderer(), sprite->texture, sprite->srcRect, &dstRect,
                         transform->angle, nullptr, SDL_FLIP_NONE);
    }
    SDL_RenderPresent(LoadResourceManager::getInstance()->GetRenderer());
}

void SpriteSystem::init() {
    System::init();
}
