//
// Created by TCT on 11/22/2024.
//

#include "ControlComponent.h"

#include <ctime>

#include "Game/Common/Time.h"
float timeCounter = 0;
float deltaTimeShooting = 0.5f;

bool ControlComponent::isUp() const {
    return this->currentKeyStates[SDL_SCANCODE_UP] || this->currentKeyStates[SDL_SCANCODE_W];
}

bool ControlComponent::isDown() const {
    return this->currentKeyStates[SDL_SCANCODE_DOWN] || this->currentKeyStates[SDL_SCANCODE_S];
}

bool ControlComponent::isLeft() const {
    return this->currentKeyStates[SDL_SCANCODE_LEFT] || this->currentKeyStates[SDL_SCANCODE_A];
}

bool ControlComponent::isRight() const {
    return this->currentKeyStates[SDL_SCANCODE_RIGHT] || this->currentKeyStates[SDL_SCANCODE_D];
}

bool ControlComponent::isShoot() const {
    timeCounter += Time::deltaTime;
    if (timeCounter >= deltaTimeShooting) {
        if (this->currentKeyStates[SDL_SCANCODE_SPACE] || this->currentKeyStates[SDL_SCANCODE_M]) {
            timeCounter = 0;
            return true;
        }
    }
    return false;
}
