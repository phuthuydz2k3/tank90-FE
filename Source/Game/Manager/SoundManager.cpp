//
// Created by TCT on 11/23/2024.
//

#include "SoundManager.h"

#include "LoadResourceManager.h"

void SoundManager::PlaySound(std::string path) {
    if (this->sounds.find(path) == this->sounds.end()) {
        Mix_Chunk *mix_chunk = LoadResourceManager::getInstance()->LoadSound(path);
        this->sounds[path] = mix_chunk;
    }
    Mix_PlayChannel(-1, this->sounds.at(path), 0);
}
