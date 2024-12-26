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
    int random = rand() % 4;
    if (random == 0) {
        path = "../Data/Images/treeSmall.png";
    } else if (random == 1) {
        path = "../Data/Images/treeLarge.png";
    } else if (random == 2) {
        path = "../Data/Images/treeBrown_large.png";
    } else {
        path = "../Data/Images/treeBrown_small.png";
    }
    sprite->texture = LoadResourceManager::getInstance()->LoadTexture(path);
    sprite->layer = 3;
    sprite->size = VECTOR2(50, 50);
    this->getComponent<Transform>()->angle = 0;
}
