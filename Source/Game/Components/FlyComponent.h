//
// Created by TCT on 11/23/2024.
//

#ifndef FLYCOMPONENT_H
#define FLYCOMPONENT_H
#include "ECS/Component/Component.h"


class FlyComponent : public Component {
public:
    FlyComponent();
    FlyComponent(float speed);

    float speed;
};


#endif //FLYCOMPONENT_H

