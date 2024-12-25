//
// Created by TCT on 10/31/2024.
//

#include "Sprite.h"

#include "Game/Manager/LoadResourceManager.h"

Sprite::Sprite() {
    this->texture = nullptr;
    this->size = VECTOR2(10, 10);
    this->srcRect = nullptr;
    this->layer = 0;
}

Sprite::Sprite(const std::string &pathSprite, const VECTOR2 &size, SDL_Rect *srcRect, int layer) {
    this->texture = LoadResourceManager::getInstance()->LoadTexture(pathSprite);
    this->size = size;
    this->srcRect = srcRect;
    this->layer = layer;
}
