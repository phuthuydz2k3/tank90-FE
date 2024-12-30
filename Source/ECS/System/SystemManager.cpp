//
// Created by TCT on 10/30/2024.
//

#include "SystemManager.h"

#include <iostream>
#include <Game/Systems/NetworkTrackingSystem.h>

#include "Game/Systems/ClickableSystem.h"
#include "Game/Systems/ControlSystem.h"
#include "Game/Systems/CursorSystem.h"
#include "Game/Systems/DestroyCounterSystem.h"
#include "Game/Systems/EffectSystem.h"
#include "Game/Systems/FlySystem.h"
#include "Game/Systems/NetworkReceiverSystem.h"
#include "Game/Systems/RectangleColliderSystem.h"
#include "Game/Systems/SpriteSystem.h"
#include "Game/Systems/TextSystem.h"
#include "Game/Systems/TransformSystem.h"
#include "Game/Systems/FootprintSystem.h"
#include <string>


void SystemManager::update() const {
    for (const auto &system: this->systems) {
        system.second->update();
    }
}

void SystemManager::init(const string& playerName, const string& roomName, const string& roomPassword) {
    this->registerSystem<TransformSystem>();
    this->registerSystem<CursorSystem>();
    this->registerSystem<DestroyCounterSystem>();
    this->registerSystem<ClickableSystem>();
    this->registerSystem<NetworkTrackingSystem>();
    this->registerSystem<NetworkReceiverSystem>(playerName, roomName, roomPassword);
    this->registerSystem<FootprintSystem>();
    this->registerSystem<ControlSystem>();
    this->registerSystem<FlySystem>();
    this->registerSystem<RectangleColliderSystem>();
    this->registerSystem<EffectSystem>();
    this->registerSystem<TextSystem>();
    this->registerSystem<SpriteSystem>();
    for (const auto &system: this->systems) {
        auto networkReceiverSystem = dynamic_cast<NetworkReceiverSystem*>(system.second.get());
        if (networkReceiverSystem) {
            networkReceiverSystem->init(playerName, roomName, roomPassword);
        } else {
            system.second->init();
        }
    }
}
