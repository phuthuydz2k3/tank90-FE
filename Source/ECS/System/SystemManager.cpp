//
// Created by TCT on 10/30/2024.
//

#include "SystemManager.h"

#include <Game/Systems/NetworkTrackingSystem.h>

#include "Game/Systems/ControlSystem.h"
#include "Game/Systems/EffectSystem.h"
#include "Game/Systems/FlySystem.h"
#include "Game/Systems/NetworkReceiverSystem.h"
#include "Game/Systems/RectangleColliderSystem.h"
#include "Game/Systems/SpriteSystem.h"


void SystemManager::update() const {
    for (const auto &system: this->systems) {
        system.second->update();
    }
}

void SystemManager::init() {
    this->registerSystem<NetworkReceiverSystem>();
    this->registerSystem<NetworkTrackingSystem>();
    this->registerSystem<ControlSystem>();
    this->registerSystem<FlySystem>();
    this->registerSystem<RectangleColliderSystem>();
    this->registerSystem<EffectSystem>();
    this->registerSystem<SpriteSystem>();
    for (const auto &system: this->systems) {
        system.second->init();
    }
}
