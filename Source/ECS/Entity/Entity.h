//
// Created by TCT on 10/30/2024.
//

#ifndef ENTITY_H
#define ENTITY_H
#include <memory>
#include <unordered_map>
#include <string>
#include "../Component/Component.h"


class Entity {
private:
    std::unordered_map<std::string, std::unique_ptr<Component> > components;
    int id;

public:
    template<typename T>
    void addComponent();

    template<typename T>
    void removeComponent();

    template<typename T>
    T *getComponent();

    template<typename T>
    bool hasComponent();

    virtual int getId();

    virtual void setId(int id);

    virtual ~Entity() = 0;
};
#endif //ENTITY_H
