//
// Created by TCT on 12/27/2024.
//

#include "Image.h"

#include "Game/Components/Sprite.h"
#include "Game/Components/Transform.h"

Image::Image() {
    this->addComponent<Transform>();
    this->addComponent<Sprite>();

    this->getComponent<Sprite>()->layer = 100;
}
