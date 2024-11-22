//
// Created by TCT on 10/30/2024.
//

#include "EntityManager.h"


void EntityManager::removeEntity(int id) {
    if (this->entities.find(id) == this->entities.end()) return;
    this->entities.erase(id);
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
