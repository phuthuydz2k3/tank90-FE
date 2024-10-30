//
// Created by TCT on 10/30/2024.
//

#include "EntityManager.h"

template<typename T>
T *EntityManager::createEntity() {
    static_assert(std::is_base_of_v<Entity, T>, "T must be derived from Entity");
    Entity *entity = new T();\
    entity->setId(this->entities.size());
    entities[entity->getId()] = std::unique_ptr<Entity>(entity);
    return entity;
}

template<typename T>
void EntityManager::removeEntity(int id) {
    static_assert(std::is_base_of_v<Entity, T>, "T must be derived from Entity");
    this->removeEntity(id);
}

void EntityManager::removeEntity(int id) {
    if (this->entities.find(id) == this->entities.end()) return;
    this->entities.erase(id);
}

template<typename T>
T *EntityManager::getEntity(int id) {
    static_assert(std::is_base_of_v<Entity, T>, "T must be derived from Entity");
    return dynamic_cast<T *>(this->entities.at(id).get());
}

Entity *EntityManager::getEntity(int id) {
    return this->entities.at(id).get();
}

template<typename T>
bool EntityManager::hasEntity(int id) {
    static_assert(std::is_base_of_v<Entity, T>, "T must be derived from Entity");
    return this->entities.find(id) != this->entities.end();
}

template<typename T>
void EntityManager::clearEntities() {
    static_assert(std::is_base_of_v<Entity, T>, "T must be derived from Entity");
    for (auto entity: this->entities) {
        if (!dynamic_cast<T *>(entity.second.get())) continue;
        this->entities.erase(entity.first);
    }
}

void EntityManager::clearEntities() {
    this->entities.clear();
}

template<typename T>
int EntityManager::getEntityCount() const {
    return this->entities.size();
}

template<typename T>
std::list<std::unique_ptr<Entity> > EntityManager::getEntitiesWithComponent() {
    static_assert(std::is_base_of_v<Component, T>, "T must be derived from Component");
    std::list<std::unique_ptr<Entity> > entitiesWithComponent;
    for (auto &entity: this->entities) {
        if (!entity.second->hasComponent<T>()) continue;
        entitiesWithComponent.push_back(std::move(entity.second));
    }
}
