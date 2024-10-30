//
// Created by TCT on 10/30/2024.
//

#include "SystemManager.h"

template<typename T>
void SystemManager::registerSystem() {
    static_assert(std::is_base_of_v<System, T>, "T must be a subclass of System");
    if (this->systems.find(typeid(T).name()) != this->systems.end()) return;
    this->systems[typeid(T).name()] = std::make_unique<T>();
}

void SystemManager::update() const {
    for (const auto& system: this->systems) {
        system.second->update();
    }
}
