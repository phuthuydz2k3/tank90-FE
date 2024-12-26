//
// Created by TCT on 12/27/2024.
//

#include "TextSystem.h"

#include "ECS/Entity/EntityManager.h"
#include "Game/Components/Transform.h"
#include "Game/Manager/LoadResourceManager.h"
#include "Game/UIs/Text.h"

void TextSystem::update() {
    System::update();
    auto entities = EntityManager::getInstance()->getEntitiesWithComponent<Text>();
    for (auto &entity: entities) {
        auto text = entity->getComponent<Text>();
        if (text->font != nullptr) {
            SDL_Surface *surface = TTF_RenderText_Solid(text->font, text->text.c_str(), text->color);
            SDL_Texture *texture = SDL_CreateTextureFromSurface(LoadResourceManager::getInstance()->GetRenderer(),
                                                                surface);
            SDL_FreeSurface(surface);
            Transform *transform = entity->getComponent<Transform>();
            SDL_Rect dstRect = {
                static_cast<int>(transform->position.x), static_cast<int>(transform->position.y),
                surface->w, surface->h
            };
            SDL_RenderCopy(LoadResourceManager::getInstance()->GetRenderer(), texture, nullptr, &dstRect);
            SDL_DestroyTexture(texture);
        }
    }
}
