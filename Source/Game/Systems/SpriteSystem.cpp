//
// Created by TCT on 11/22/2024.
//

#include "SpriteSystem.h"
#include "ECS/Entity/EntityManager.h"
#include "Game/Manager/LoadResourceManager.h"
#include "Game/Components/Sprite.h"
#include "Game/Components/Transform.h"

class Transform;
class Sprite;


void SpriteSystem::update() {
    System::update();
    auto entities = EntityManager::getInstance()->getEntitiesWithComponent<Sprite>();
    if (entities.empty()) return;
    entities.sort([] (Entity* a, Entity* b) {
        return a->getComponent<Sprite>()->layer < b->getComponent<Sprite>()->layer;
    });

    for (const auto &entity: entities) {
        const Sprite *sprite = entity->getComponent<Sprite>();
        if (sprite->texture == nullptr) continue;
        const Transform *transform = entity->getComponent<Transform>();
        SDL_Rect dstRect = {
            static_cast<int>(transform->position.x - sprite->size.x * transform->scale.x / 2),
            static_cast<int>(transform->position.y - sprite->size.y * transform->scale.y / 2),
            static_cast<int>(sprite->size.x * transform->scale.x),
            static_cast<int>(sprite->size.y * transform->scale.y)
        };
        SDL_RenderCopyEx(LoadResourceManager::getInstance()->GetRenderer(), sprite->texture, sprite->srcRect, &dstRect,
                         transform->angle, nullptr, SDL_FLIP_NONE);
    }
}


void SpriteSystem::init() {
    System::init();
}
