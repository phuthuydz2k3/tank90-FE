//
// Created by TCT on 12/26/2024.
//

#include "UIManager.h"
#include "Game/UIs/WinUI.h"

void UIManager::Init() {
    this->addUIUnit<WinUI>();
}
