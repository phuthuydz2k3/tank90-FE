#include "Button.h"
#include "Clickable.h"
#include "Game/Components/Sprite.h"
#include "Game/Components/Transform.h"

Button::Button() {
    this->addComponent<Sprite>();
    this->addComponent<Transform>();
    this->addComponent<Clickable>();

    this->getComponent<Sprite>()->layer = 100;
}
