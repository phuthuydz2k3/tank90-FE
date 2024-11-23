//
// Created by TCT on 11/23/2024.
//

#include "Effect.h"

Effect::Effect() {
    this->size = VECTOR2(0, 0);
    this->timePerFrame = 0.25f;
}

Effect::Effect(const VECTOR2 &size, const float timePerFrame) {
    this->size = size;
    this->timePerFrame = timePerFrame;
}
