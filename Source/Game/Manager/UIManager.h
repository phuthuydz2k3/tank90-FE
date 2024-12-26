//
// Created by TCT on 12/26/2024.
//

#ifndef UIMANAGER_H
#define UIMANAGER_H
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include "SingletonTemplate.h"
#include "Game/UIs/UIUnit.h"
#include <typeinfo>


class UIManager : public SingletonTemplate<UIManager> {
public:
    std::unordered_map<std::string, std::unique_ptr<UIUnit> > uiUnits;

    void Init();

    template<typename T>
    void addUIUnit() {
        auto uiUnit = std::make_unique<T>();
        this->uiUnits[typeid(T).name()] = std::move(uiUnit);
    }

    template<typename T>
    void openUIUnit() {
        for (auto &uiUnit: uiUnits) {
            if (typeid(T).name() == uiUnit.first) continue;
            uiUnit.second->Close();
        }
        this->uiUnits[typeid(T).name()]->Init();
    }

    template<typename T>
    void closeUIUnit() {
        for (auto &uiUnit: uiUnits) {
            this->uiUnits[typeid(T).name()]->Close();
        }
    }
};


#endif //UIMANAGER_H
