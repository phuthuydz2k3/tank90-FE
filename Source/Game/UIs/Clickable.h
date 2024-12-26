#ifndef CLICKABLE_H
#define CLICKABLE_H

#include "ECS/Component/Component.h"
#include "Math/Vector2.h"

class Clickable : public Component {
public:
    VECTOR2 size;
    void (*onClick)();
};

#endif // CLICKABLE_H