//
// Created by TCT on 10/30/2024.
//

#include "Entity.h"

template<typename T>
void Entity::addComponent() {
    static_assert(std::is_base_of_v<Component, T>, "T must be a component");
    if(this->components.find(typeid(T).name()) != this->components.end()) return;
    this->components[typeid(T).name()] = std::make_unique<T>();
}

template<typename T>
void Entity::removeComponent() {
    static_assert(std::is_base_of_v<Component, T>, "T must be a component");
    this->components.erase(typeid(T).name());
}

template<typename T>
T *Entity::getComponent() {
    static_assert(std::is_base_of_v<Component, T>, "T must be a component");
    return dynamic_cast<T *>(this->components.at(typeid(T).name()).get());
}

template<typename T>
bool Entity::hasComponent() {
    static_assert(std::is_base_of_v<Component, T>, "T must be a component");
    return this->components.find(typeid(T).name()) != this->components.end();
}

int Entity::getId() {
    return this->id;
}

void Entity::setId(int id) {
    this->id = id;
}
