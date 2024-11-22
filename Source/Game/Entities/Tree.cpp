//
// Created by TCT on 11/23/2024.
//

#include "Tree.h"

#include "Game/LoadResourceManager.h"
#include "Game/Components/Sprite.h"
#include "Game/Components/Transform.h"

Tree::Tree() {
    this->addComponent<Transform>();
    this->addComponent<Sprite>();
    Sprite *sprite = this->getComponent<Sprite>();
    sprite->texture = LoadResourceManager::getInstance()->LoadTexture("../Data/Images/trees.png");
    sprite->layer = 3;
    sprite->size = VECTOR2(50, 50);
}
