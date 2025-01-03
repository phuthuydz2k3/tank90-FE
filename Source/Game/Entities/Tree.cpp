//
// Created by TCT on 11/23/2024.
//

#include "Tree.h"

#include "Game/Manager/LoadResourceManager.h"
#include "Game/Components/Sprite.h"
#include "Game/Components/Transform.h"

Tree::Tree() {
    this->addComponent<Transform>();
    this->addComponent<Sprite>();
    Sprite *sprite = this->getComponent<Sprite>();
    std::string path;
    int random = rand() % 2;
    if (random == 0) {
        path = "../Data/Images/treeSmall.png";
    } else {
        path = "../Data/Images/treeLarge.png";
    }
    sprite->texture = LoadResourceManager::getInstance()->LoadTexture(path);
    sprite->layer = 3;
    sprite->size = VECTOR2(50, 50);
    this->getComponent<Transform>()->angle = 0;
}
