//
// Created by TCT on 10/30/2024.
//

#include "Entity.h"


Entity::~Entity() {
}

int Entity::getId() {
    return this->id;
}

void Entity::setId(int id) {
    this->id = id;
}
