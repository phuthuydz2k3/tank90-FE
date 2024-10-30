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


class EntityManager : SingletonTemplate<EntityManager> {
private:
    std::unordered_map<int, std::unique_ptr<Entity> > entities;

public:
    template<typename T>
    T *createEntity();

    template<typename T>
    void removeEntity(int id);

    void removeEntity(int id);

    template<typename T>
    T *getEntity(int id);

    Entity *getEntity(int id);

    template<typename T>
    bool hasEntity(int id);

    template<typename T>
    void clearEntities();

    void clearEntities();

    template<typename T>
    int getEntityCount() const;

    template<typename T>
    std::list<std::unique_ptr<Entity>> getEntitiesWithComponent();
};



#endif //ENTITYMANAGER_H
