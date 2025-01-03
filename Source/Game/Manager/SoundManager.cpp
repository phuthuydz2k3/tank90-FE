//
// Created by TCT on 11/23/2024.
//

#include "SoundManager.h"

#include "LoadResourceManager.h"

void SoundManager::PlaySound(std::string path, bool isLoop) {
    if (this->sounds.find(path) == this->sounds.end()) {
        Mix_Chunk *mix_chunk = LoadResourceManager::getInstance()->LoadSound(path);
        this->sounds[path] = mix_chunk;
    }
    Mix_PlayChannel(SOUNDCHANNEL, this->sounds.at(path), isLoop ? -1 : 0);
}

void SoundManager::PlayEffect(std::string path, bool isLoop) {
    if (this->sounds.find(path) == this->sounds.end()) {
        Mix_Chunk *mix_chunk = LoadResourceManager::getInstance()->LoadSound(path);
        this->sounds[path] = mix_chunk;
    }
    Mix_PlayChannel(EFFECTCHANNEL, this->sounds.at(path), isLoop ? -1 : 0);
}

void SoundManager::SetVolume(int volume, int channel) {
    Mix_Volume(channel, volume);
}

void SoundManager::setMute(bool cond) {
    int volume = cond ? 0 : 30;
    this->SetVolume(volume, this->SOUNDCHANNEL);
    this->SetVolume(volume, this->EFFECTCHANNEL);
}
