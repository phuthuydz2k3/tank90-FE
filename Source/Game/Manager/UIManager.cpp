//
// Created by TCT on 12/26/2024.
//

#include "UIManager.h"

#include "Game/UIs/GameplayUI.h"
#include "Game/UIs/LeaderBoardUI.h"
#include "Game/UIs/LoseUI.h"
#include "Game/UIs/PauseUI.h"
#include "Game/UIs/WinUI.h"

void UIManager::Init() {
    this->addUIUnit<WinUI>();
    this->addUIUnit<LoseUI>();
    this->addUIUnit<PauseUI>();
    this->addUIUnit<GameplayUI>();
    this->addUIUnit<LeaderBoardUI>();
}
