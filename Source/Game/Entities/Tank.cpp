//
// Created by TCT on 11/22/2024.
//

#include "Tank.h"

#include "Game/Components/Effect.h"
#include "Game/Components/RectangleCollider.h"
#include "Game/Systems/RectangleColliderSystem.h"

Tank::Tank() {
    this->addComponent<Transform>();
    this->addComponent<Sprite>();
    this->addComponent<ControlComponent>();
    this->addComponent<RectangleCollider>();
    this->addComponent<Effect>();

    this->getComponent<Transform>()->angle = 0;
    const auto sprite = this->getComponent<Sprite>();
    sprite->texture = LoadResourceManager::getInstance()->LoadTexture("../Data/Images/green_tank.png");
    sprite->srcRect = new SDL_Rect{0, 0, 16, 16};
    sprite->size = {50, 50};
    ControlComponent *control = this->getComponent<ControlComponent>();
    control->speed = 100;
    control->rotationSpeed = 100;
    this->getComponent<RectangleCollider>()->size = {50, 50};
    this->getComponent<RectangleCollider>()->layer = Player;
    auto effect = this->getComponent<Effect>();
    std::list<Frame> frames;
    frames.push_back({LoadResourceManager::getInstance()->LoadTexture("../Data/Images/undie_circle_1.png"), nullptr});
    frames.push_back({LoadResourceManager::getInstance()->LoadTexture("../Data/Images/undie_circle_2.png"), nullptr});
    effect->frames = frames;
    effect->size = {50, 50};
    effect->timePerFrame = 0.5f;
    effect->loop = 3;
    effect->onEnd = [this] {
        this->removeComponent<Effect>();
    };
}
