//
// Created by TCT on 12/27/2024.
//

#ifndef TEXT_H
#define TEXT_H
#include <SDL_ttf.h>
#include <string>

#include "ECS/Component/Component.h"


class Text : Component {
public:
    TTF_Font *font;
    SDL_Color color;
    std::string text;
    Text();
};



#endif //TEXT_H
