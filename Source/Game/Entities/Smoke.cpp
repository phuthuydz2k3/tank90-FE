//
// Created by TCT on 12/27/2024.
//

#include "Smoke.h"

#include "Game/Components/Effect.h"
#include "Game/Components/Transform.h"
#include "Game/Manager/LoadResourceManager.h"

Smoke::Smoke() {
    this->addComponent<Transform>();
    this->addComponent<Effect>();
    std::list<Frame> frames;
    frames.push_back(Frame({
        LoadResourceManager::getInstance()->LoadTexture("../Data/Images/Smoke/smokeGrey0.png"), nullptr
    }));
    frames.push_back(Frame({
        LoadResourceManager::getInstance()->LoadTexture("../Data/Images/Smoke/smokeGrey1.png"), nullptr
    }));
    frames.push_back(Frame({
        LoadResourceManager::getInstance()->LoadTexture("../Data/Images/Smoke/smokeGrey2.png"), nullptr
    }));
    frames.push_back(Frame({
        LoadResourceManager::getInstance()->LoadTexture("../Data/Images/Smoke/smokeGrey3.png"), nullptr
    }));
    frames.push_back(Frame({
        LoadResourceManager::getInstance()->LoadTexture("../Data/Images/Smoke/smokeGrey4.png"), nullptr
    }));
    frames.push_back(Frame({
        LoadResourceManager::getInstance()->LoadTexture("../Data/Images/Smoke/smokeGrey5.png"), nullptr
    }));
    this->getComponent<Effect>()->frames = frames;
}
