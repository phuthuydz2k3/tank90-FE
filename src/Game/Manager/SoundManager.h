//
// Created by TCT on 11/23/2024.
//

#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H
#include <map>
#include <SDL_mixer.h>
#include <string>

#include "SingletonTemplate.h"


class SoundManager : public SingletonTemplate<SoundManager> {
public:
    void PlaySound(std::string path);

private:
    std::map<std::string, Mix_Chunk *> sounds;
};


#endif //SOUNDMANAGER_H
