//
// Created by TCT on 12/26/2024.
//

#ifndef BEDESTROY_H
#define BEDESTROY_H
#include "ECS/Component/Component.h"


class BeDestroy : public Component {
public:
    void Destroy();
    bool isDestroyed = false;
};



#endif //BEDESTROY_H
