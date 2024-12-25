//
// Created by TCT on 11/24/2024.
//

#include "CollideExplosion.h"

#include "Game/Components/Effect.h"
#include "Game/Components/Transform.h"
#include "Game/Manager/LoadResourceManager.h"

CollideExplosion::CollideExplosion() {
    this->addComponent<Transform>();
    this->addComponent<Effect>();
    std::list<Frame> frames;
    frames.push_back(Frame({LoadResourceManager::getInstance()->LoadTexture("../Data/Images/destroy_1.png"), nullptr}));
    frames.push_back(Frame({LoadResourceManager::getInstance()->LoadTexture("../Data/Images/destroy_2.png"), nullptr}));
    frames.push_back(Frame({LoadResourceManager::getInstance()->LoadTexture("../Data/Images/destroy_3.png"), nullptr}));
    this->getComponent<Effect>()->frames = frames;
}
