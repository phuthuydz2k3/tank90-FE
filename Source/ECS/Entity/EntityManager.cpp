//
// Created by TCT on 10/30/2024.
//

#include "EntityManager.h"

std::list<int> backupRemoveEntities = {};

void EntityManager::removeEntity(int id) {
    if (this->entities.find(id) == this->entities.end()) return;
    backupRemoveEntities.push_back(id);
    // this->entities.erase(id);
}


Entity *EntityManager::getEntity(int id) const {
    return this->entities.at(id).get();
}


void EntityManager::clearEntities() {
    this->entities.clear();
}

int EntityManager::getEntityCount() const {
    return this->entities.size();
}

void EntityManager::lateUpdate() {
    for (auto &id: backupRemoveEntities) {
        this->entities.erase(id);
    }
    backupRemoveEntities.clear();
}
