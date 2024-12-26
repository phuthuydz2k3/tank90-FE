//
// Created by TCT on 12/27/2024.
//

#include "Mouse.h"

#include "Game/Components/Cursor.h"
#include "Game/Components/Sprite.h"
#include "Game/Components/Transform.h"
#include "Game/Manager/LoadResourceManager.h"

Mouse::Mouse() {
    this->addComponent<Transform>();
    this->addComponent<Sprite>();
    this->addComponent<Cursor>();

    this->getComponent<Transform>()->angle = 0;
    Sprite *sprite = this->getComponent<Sprite>();
    sprite->texture = LoadResourceManager::getInstance()->LoadTexture("../Data/Images/target_a.png");
    sprite->size = VECTOR2(30, 30);
    sprite->layer = 1000;
    SDL_ShowCursor(false);
}
