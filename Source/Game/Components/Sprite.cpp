//
// Created by TCT on 10/31/2024.
//

#include "Sprite.h"

#include "Game/LoadResourceManager.h"

Sprite::Sprite() {
    this->texture = nullptr;
    this->size = VECTOR2(10, 10);
    this->srcRect = nullptr;
}

Sprite::Sprite(const std::string &pathSprite, const VECTOR2 &size, SDL_Rect *srcRect) {
    this->texture = LoadResourceManager::getInstance()->LoadTexture(pathSprite);
    this->size = size;
    this->srcRect = srcRect;
}
