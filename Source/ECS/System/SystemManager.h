//
// Created by TCT on 10/30/2024.
//

#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H
#include <memory>
#include <unordered_map>
#include <string>
#include "System.h"
#include "../../SingletonTemplate.h"


class SystemManager : public SingletonTemplate<SystemManager> {
private:
    std::unordered_map<std::string, std::unique_ptr<System> > systems;

public:
    template<typename T>
    void registerSystem() {
        static_assert(std::is_base_of_v<System, T>, "T must be a subclass of System");
        if (this->systems.find(typeid(T).name()) != this->systems.end()) return;
        this->systems[typeid(T).name()] = std::make_unique<T>();
    }

    void update() const;
    void init();
};


#endif //SYSTEMMANAGER_H
