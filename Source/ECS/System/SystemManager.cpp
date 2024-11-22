//
// Created by TCT on 10/30/2024.
//

#include "SystemManager.h"


void SystemManager::update() const {
    for (const auto &system: this->systems) {
        system.second->update();
    }
}

void SystemManager::init() {
}
