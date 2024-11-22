//
// Created by TCT on 11/22/2024.
//

#include "Tank.h"

#include "Game/Systems/ControlSystem.h"

Tank::Tank() {
    this->addComponent<Transform>();
    this->addComponent<Sprite>();
    this->addComponent<ControlComponent>();
    this->getComponent<Transform>()->angle = 0;
    auto sprite = this->getComponent<Sprite>();
    sprite->texture = LoadResourceManager::getInstance()->LoadTexture("../Data/Images/green_tank.png");
    sprite->srcRect = new SDL_Rect{0, 0, 16, 16};
    sprite->size = {50, 50};
    ControlComponent *control = this->getComponent<ControlComponent>();
    control->speed = 100;
    control->rotationSpeed = 100;
}
