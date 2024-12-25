//
// Created by TCT on 11/24/2024.
//

#include "EffectSystem.h"

#include "ECS/Entity/EntityManager.h"
#include "Game/Common/Time.h"
#include "Game/Components/Effect.h"
#include "Game/Components/Transform.h"
#include "Game/Manager/LoadResourceManager.h"
float timeCount = 0;

void EffectSystem::update() {
    System::update();
    const auto entities = EntityManager::getInstance()->getEntitiesWithComponent<Effect>();
    for (auto &entity: entities) {
        Effect *effect = entity->getComponent<Effect>();
        Transform *transform = entity->getComponent<Transform>();
        effect->timeCount += Time::deltaTime;
        SDL_Rect pos = {
            static_cast<int>(transform->position.x - effect->size.x * transform->scale.x / 2),
            static_cast<int>(transform->position.y - effect->size.y * transform->scale.y / 2),
            static_cast<int>(effect->size.x * transform->scale.x),
            static_cast<int>(effect->size.y * transform->scale.y)
        };
        auto it = effect->frames.begin();
        std::advance(it, effect->currentFrame);
        SDL_Texture *texture = it->texture;
        SDL_RenderCopyEx(LoadResourceManager::getInstance()->GetRenderer(), texture, it->srcRect, &pos,
                         transform->angle, nullptr, SDL_FLIP_NONE);
        if (effect->timeCount >= effect->timePerFrame) {
            effect->timeCount = 0;
            effect->currentFrame++;
            if (effect->currentFrame >= effect->frames.size()) {
                if (effect->loop == -1 || effect->currentLoop < effect->loop) {
                    effect->currentFrame = 0;
                    effect->currentLoop++;
                } else {
                    if (effect->onEnd != nullptr) {
                        effect->onEnd();
                    }
                }
            }
        }
    }
}
