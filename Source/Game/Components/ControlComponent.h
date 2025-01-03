//
// Created by TCT on 11/22/2024.
//

#ifndef CONTROLCOMPONENT_H
#define CONTROLCOMPONENT_H
#include <SDL_keyboard.h>
#include <SDL_stdinc.h>

#include "ECS/Component/Component.h"


class ControlComponent : public Component {
public:
    const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);
    bool isPaused = false;

    bool isUp() const;

    bool isDown() const;

    bool isLeft() const;

    bool isRight() const;

    bool isShoot();

    bool isSpecialShoot();

    bool isSpeedup() const;

    float speed;
    float rotationSpeed;
    bool isShooting = false;
};


#endif //CONTROLCOMPONENT_H
