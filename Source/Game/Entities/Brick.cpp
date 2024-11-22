//
// Created by TCT on 11/23/2024.
//

#include "Brick.h"

#include "ECS/Entity/EntityManager.h"
#include "Game/LoadResourceManager.h"
#include "Game/Components/RectangleCollider.h"
#include "Game/Components/Sprite.h"
#include "Game/Components/Transform.h"


Brick::Brick() {
    this->addComponent<Transform>();
    this->addComponent<Sprite>();
    this->addComponent<RectangleCollider>();
    Sprite *sprite = this->getComponent<Sprite>();
    sprite->texture = LoadResourceManager::getInstance()->LoadTexture("../Data/Images/brick.png");
    sprite->size = {50, 50};
    this->getComponent<Transform>()->angle = 0;
    this->getComponent<RectangleCollider>()->size = {50, 50};
    this->getComponent<RectangleCollider>()->isStatic = true;
}
