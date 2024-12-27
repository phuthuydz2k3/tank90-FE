//
// Created by TCT on 11/25/2024.
//

#include "GameplayService.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "ECS/Entity/EntityManager.h"
#include "Game/Components/NetworkReceiver.h"
#include "Game/Components/Transform.h"
#include "Game/Entities/Brick.h"
#include "Game/Entities/SpawnPoint.h"
#include "Game/Entities/Tank.h"
#include "Game/Entities/Tree.h"
#include <filesystem>

#include "Game/Common/ActionStatePacket.h"
#include "Game/Components/NetworkTracking.h"
#include "Game/Entities/GameObject.h"
#include "Game/Entities/Mouse.h"

#include "Game/Manager/UIManager.h"
#include "Game/UIs/GameplayUI.h"
#include "Game/UIs/LoseUI.h"
#include "Game/UIs/WinUI.h"

class NetworkTracking;
class Tank;

bool isDigit(const std::string &str) {
    return std::all_of(str.begin(), str.end(), ::isdigit);
}

std::vector<int> convertToNumbers(const std::string &str) {
    std::stringstream ss(str);
    std::string word;
    std::vector<int> numbers;

    while (ss >> word) {
        numbers.push_back(std::stoi(word));
    }
    return numbers;
}

void LoadBorder() {
    for (int i = 0; i < 16; i++) {
        EntityManager::getInstance()->createEntity<Brick>()->getComponent<Transform>()->position = VECTOR2(
            -25.0f, i * 50 + 25);
        EntityManager::getInstance()->createEntity<Brick>()->getComponent<Transform>()->position = VECTOR2(
            16 * 50 + 25, i * 50 + 25);
        EntityManager::getInstance()->createEntity<Brick>()->getComponent<Transform>()->position = VECTOR2(
            i * 50 + 25, -25.0f);
        EntityManager::getInstance()->createEntity<Brick>()->getComponent<Transform>()->position = VECTOR2(
            i * 50 + 25, 16 * 50 + 25);
    }
}

void LoadEnvironment() {
    std::string path;
    int random = rand() % 2;
    if (random == 0) {
        path = "../Data/Images/dirt.png";
    } else {
        path = "../Data/Images/sand.png";
    }
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            GameObject *environment = EntityManager::getInstance()->createEntity<GameObject>();
            environment->addComponent<Transform>();
            environment->addComponent<Sprite>();
            environment->getComponent<Sprite>()->texture = LoadResourceManager::getInstance()->LoadTexture(
                path);
            environment->getComponent<Sprite>()->size = {50, 50};
            environment->getComponent<Transform>()->position = VECTOR2(j * 50 + 25, i * 50 + 25);
            environment->getComponent<Sprite>()->layer = -2;
            environment->getComponent<Transform>()->angle = 0;
        }
    }
}

void GameplayService::LoadMap(int mapIndex) const {
    std::fstream fin;
    fin.open(this->dataPath, std::ios::in);
    if (!fin.is_open()) {
        std::cerr << "Error: file not found\n";
        return;
    }
    int roll;
    std::vector<std::string> row;
    std::string line, word;
    while (std::getline(fin, line)) {
        row.clear();
        std::stringstream s(line);
        while (std::getline(s, word, ',')) {
            row.push_back(word);
        }

        if (row.empty()) continue;
        if (!isDigit(row[0])) continue;

        roll = std::stoi(row[0]);

        if (roll == mapIndex) {
            std::vector<int> brickIndexes = convertToNumbers(row[1]);
            std::vector<int> treeIndexes = convertToNumbers(row[2]);
            std::vector<int> playerIndex = convertToNumbers(row[3]);
            LoadBorder();
            LoadEnvironment();
            for (auto &index: brickIndexes) {
                int row = index / 16;
                int col = index % 16;
                EntityManager::getInstance()->createEntity<Brick>()->getComponent<Transform>()->position = VECTOR2(
                    col * 50 + 25, row * 50 + 25);
            }
            for (auto &index: treeIndexes) {
                int row = index / 16;
                int col = index % 16;
                EntityManager::getInstance()->createEntity<Tree>()->getComponent<Transform>()->position = VECTOR2(
                    col * 50 + 25, row * 50 + 25);
            }
            int row = playerIndex[0] / 16;
            int col = playerIndex[0] % 16;
            EntityManager::getInstance()->createEntity<SpawnPoint>()->getComponent<Transform>()->position = VECTOR2(
                col * 50 + 25, row * 50 + 25);
        }
    }
}

void GameplayService::LoseGame() const {
    UIManager::getInstance()->openUIUnit<LoseUI>();
    this->PauseGame(true);
}

void GameplayService::WinGame() const {
    UIManager::getInstance()->openUIUnit<WinUI>();
    this->PauseGame(true);
}

void GameplayService::EnterGame() const {
    UIManager::getInstance()->openUIUnit<GameplayUI>();
    EntityManager::getInstance()->createEntity<Mouse>();
}

void GameplayService::PauseGame(bool isPause) const {
    auto entities = EntityManager::getInstance()->getEntitiesWithComponent<ControlComponent>();
    for (auto &entity: entities) {
        entity->getComponent<ControlComponent>()->isPaused = isPause;
    }
}

void GameplayService::outGame() const {
    // Create a packet to notify the server
    ActionStatePacket packet;
    packet.type = 1;
    packet.id = NetworkTracking::id;
    packet.isOut = true;

    boost::system::error_code error;
    boost::asio::write(NetworkReceiver::tcpSocket, boost::asio::buffer(&packet, sizeof(ActionStatePacket)), error);

    if (error) {
        std::cerr << "Failed to send packet: " << error.message() << std::endl;
    } else {
        std::cout << "Notified server that client " << NetworkTracking::id << " is out of the game." << std::endl;
    }
}
