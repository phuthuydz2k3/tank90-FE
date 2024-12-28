//
// Created by TCT on 10/30/2024.
//

#ifndef COMPONENT_H
#define COMPONENT_H

class Component {
public:
    void* owner = nullptr;
    Component() = default;
    virtual ~Component() = default;
};

#endif //COMPONENT_H
