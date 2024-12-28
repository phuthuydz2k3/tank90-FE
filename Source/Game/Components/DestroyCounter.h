//
// Created by TCT on 11/23/2024.
//

#ifndef DESTROYCOUNTER_H
#define DESTROYCOUNTER_H
#include "ECS/Component/Component.h"


class DestroyCounter : public Component {
public:
    DestroyCounter();
    DestroyCounter(float time);
    float timeCounter;
    float countTime = 0.0f;
};


#endif //DESTROYCOUNTER_H
