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
    void registerSystem();

    void update() const;
};


#endif //SYSTEMMANAGER_H
