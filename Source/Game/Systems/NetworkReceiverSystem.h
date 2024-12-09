//
// Created by TCT on 12/9/2024.
//

#ifndef NETWORKRECEIVERSYSTEM_H
#define NETWORKRECEIVERSYSTEM_H

#include "ECS/System/System.h"

class NetworkReceiverSystem : public System{
public:
    void update() override;
    void init() override;
};



#endif //NETWORKRECEIVERSYSTEM_H
