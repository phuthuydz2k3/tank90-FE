#ifndef ENTITY_H
#define ENTITY_H

#include <memory>
#include <unordered_map>
#include <string>
#include "../Component/Component.h"

class Entity {
protected:
    std::unordered_map<std::string, std::unique_ptr<Component> > components;
    int id;

public:
    virtual ~Entity();

    template<typename T>
    void addComponent() {
        static_assert(std::is_base_of_v<Component, T>, "T must be a component");
        if (this->components.find(typeid(T).name()) != this->components.end()) return;
        this->components[typeid(T).name()] = std::unique_ptr<Component>(std::make_unique<T>());
    }

    template<typename T>
    void removeComponent() {
        static_assert(std::is_base_of_v<Component, T>, "T must be a component");
        this->components.erase(typeid(T).name());
    }

    template<typename T>
    T *getComponent() {
        static_assert(std::is_base_of_v<Component, T>, "T must be a component");
        if (this->components.find(typeid(T).name()) != this->components.end()) {
            return dynamic_cast<T *>(this->components.at(typeid(T).name()).get());
        }
        return nullptr;
    }

    template<typename T>
    bool hasComponent() {
        static_assert(std::is_base_of_v<Component, T>, "T must be a component");
        return this->components.find(typeid(T).name()) != this->components.end();
    }

    virtual int getId();

    virtual void setId(int id);
};

#endif // ENTITY_H
