//
// Created by TCT on 10/30/2024.
//

#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H
#include <list>
#include <memory>
#include <unordered_map>
#include "Entity.h"
#include "../../SingletonTemplate.h"
#include <random>

class EntityManager : public SingletonTemplate<EntityManager> {
private:
    std::unordered_map<int, std::unique_ptr<Entity> > entities;

public:
    template<typename T>
    T *createEntity() {
        static_assert(std::is_base_of_v<Entity, T>, "T must be derived from Entity");
        T *entity = new T();
        int id = 0;
        do {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::  uniform_int_distribution<> dis(0, 1000000);
            id = dis(gen);
        } while (this->hasEntity<Entity>(id));
        entity->setId(id);
        entities[entity->getId()] = std::unique_ptr<Entity>(entity);
        return entity;
    }

    template<typename T>
    void removeEntity(int id) {
        static_assert(std::is_base_of_v<Entity, T>, "T must be derived from Entity");
        this->removeEntity(id);
    }

    void removeEntity(int id);

    template<typename T>
    T *getEntity(int id) {
        static_assert(std::is_base_of_v<Entity, T>, "T must be derived from Entity");
        return dynamic_cast<T *>(this->entities.at(id).get());
    }

    Entity *getEntity(int id) const;

    template<typename T>
    bool hasEntity(int id) {
        static_assert(std::is_base_of_v<Entity, T>, "T must be derived from Entity");
        return this->entities.find(id) != this->entities.end();
    }

    void clearEntities();

    int getEntityCount() const;

    template<typename T>
    std::list<Entity *> getEntitiesWithComponent() const {
        static_assert(std::is_base_of_v<Component, T>, "T must be derived from Component");
        std::list<Entity *> entitiesWithComponent;
        for (auto &entity: this->entities) {
            if (!entity.second->hasComponent<T>()) continue;
            entitiesWithComponent.push_back(entity.second.get());
        }
        return entitiesWithComponent;
    }

    void lateUpdate();
};


#endif //ENTITYMANAGER_H
