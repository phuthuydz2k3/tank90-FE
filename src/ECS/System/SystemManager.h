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

using namespace std;


class SystemManager : public SingletonTemplate<SystemManager> {
private:
    std::unordered_map<std::string, std::unique_ptr<System> > systems;

public:
    template<typename T, typename... Args>
    void registerSystem(Args&&... args) {
        static_assert(std::is_base_of_v<System, T>, "T must be a subclass of System");
        if (this->systems.find(typeid(T).name()) != this->systems.end()) return;
        this->systems[typeid(T).name()] = std::make_unique<T>(std::forward<Args>(args)...);
    }

    void update() const;
    void init(const string& playerName, const string& roomName, const string& roomPassword);
};


#endif //SYSTEMMANAGER_H
