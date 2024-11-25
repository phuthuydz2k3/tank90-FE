//
// Created by TCT on 11/25/2024.
//

#include "GameplayService.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "ECS/Entity/EntityManager.h"
#include "Game/Components/Transform.h"
#include "Game/Entities/Brick.h"
#include "Game/Entities/SpawnPoint.h"
#include "Game/Entities/Tree.h"

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
