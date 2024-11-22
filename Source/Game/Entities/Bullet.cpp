//
// Created by TCT on 11/23/2024.
//

#include "Bullet.h"

#include "Game/Components/DestroyCounter.h"

Bullet::Bullet() {
    this->addComponent<Transform>();
    this->addComponent<Sprite>();
    this->addComponent<FlyComponent>();
    // this->addComponent<DestroyCounter>();
    Sprite *sprite = this->getComponent<Sprite>();
    sprite->texture = LoadResourceManager::getInstance()->LoadTexture("../Data/Images/bulletUp.png");
    sprite->size = {10, 10};
    this->getComponent<Transform>()->angle = 0;
    this->getComponent<FlyComponent>()->speed = 200;
}
