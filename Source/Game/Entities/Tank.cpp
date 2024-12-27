//
// Created by TCT on 11/22/2024.
//

#include "Tank.h"

#include "GameObject.h"
#include "ECS/Entity/EntityManager.h"
#include "Game/Components/Effect.h"
#include "Game/Components/Footprint.h"
#include "Game/Components/NetworkTracking.h"
#include "Game/Components/RectangleCollider.h"
#include "Game/Feature/BeDestroy.h"
#include "Game/Systems/RectangleColliderSystem.h"

Tank::Tank() {
    this->addComponent<Transform>();
    this->addComponent<Sprite>();
    this->addComponent<ControlComponent>();
    this->addComponent<RectangleCollider>();
    this->addComponent<Effect>();
    this->addComponent<NetworkTracking>();
    this->addComponent<BeDestroy>();
    this->addComponent<Footprint>();

    this->getComponent<Transform>()->angle = 0;
    const auto sprite = this->getComponent<Sprite>();
    sprite->texture = LoadResourceManager::getInstance()->LoadTexture("../Data/Images/tankGreen_outline.png");
    sprite->size = {30, 30};
    ControlComponent *control = this->getComponent<ControlComponent>();
    control->speed = 100;
    control->rotationSpeed = 100;
    this->getComponent<RectangleCollider>()->size = {30, 30};
    this->getComponent<RectangleCollider>()->layer = Player;
    auto effect = this->getComponent<Effect>();
    std::list<Frame> frames;
    frames.push_back({LoadResourceManager::getInstance()->LoadTexture("../Data/Images/undie_circle_1.png"), nullptr});
    frames.push_back({LoadResourceManager::getInstance()->LoadTexture("../Data/Images/undie_circle_2.png"), nullptr});
    effect->frames = frames;
    effect->size = {30, 30};
    effect->timePerFrame = 0.5f;
    effect->loop = 3;
    effect->onEnd = [this] {
        this->removeComponent<Effect>();
    };
    this->getComponent<NetworkTracking>()->typeTracking = 0;
}
