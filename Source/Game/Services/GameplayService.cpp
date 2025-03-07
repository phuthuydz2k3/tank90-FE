//
// Created by TCT on 11/25/2024.
//

#include "GameplayService.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>
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
#include "Game/Manager/SoundManager.h"

#include "Game/Manager/UIManager.h"
#include "Game/UIs/GameplayUI.h"
#include "Game/UIs/LeaderBoardUI.h"
#include "Game/UIs/LoseUI.h"
#include "Game/UIs/WinUI.h"
#include <boost/asio.hpp>

std::vector<Entity *> backGrounds;
std::vector<Entity *> trees;

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
    std::string path = "../Data/Images/dirt.png";
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
            backGrounds.push_back(environment);
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
                Tree *tree = EntityManager::getInstance()->createEntity<Tree>();
                tree->getComponent<Transform>()->position = VECTOR2(
                    col * 50 + 25, row * 50 + 25);
                trees.push_back(tree);
            }
            // Seed the random number generator
            std::srand(static_cast<unsigned int>(std::time(nullptr)));
            int randomTree = treeIndexes[rand() % treeIndexes.size()];
            int row = randomTree / 16;
            int col = randomTree % 16;
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
    this->NotifyServerForWinGame();
    // this->GetLeaderBoard();
}

void GameplayService::EnterGame() const {
    UIManager::getInstance()->openUIUnit<GameplayUI>();
    EntityManager::getInstance()->createEntity<Mouse>();
    SoundManager::getInstance()->PlaySound("../Data/Audio/BGM/bgm.wav", true);
    SoundManager::getInstance()->SetVolume(30, SoundManager::getInstance()->SOUNDCHANNEL);
    SoundManager::getInstance()->SetVolume(50, SoundManager::getInstance()->EFFECTCHANNEL);
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

void GameplayService::NotifyServerForWinGame() const {
    // Create a packet to notify the server
    ActionStatePacket packet;
    packet.type = 4;
    packet.id = NetworkTracking::id;

    boost::system::error_code error;
    boost::asio::write(NetworkReceiver::tcpSocket, boost::asio::buffer(&packet, sizeof(ActionStatePacket)), error);

    if (error) {
        std::cerr << "Failed to send packet: " << error.message() << std::endl;
    } else {
        std::cout << "Notified server that client " << NetworkTracking::id << " win the game and need update score" <<
                std::endl;
    }
}

void GameplayService::ChangeTheme(int themeIndex) const {
    if (themeIndex == 0) {
        for (auto &background: backGrounds) {
            background->getComponent<Sprite>()->texture = LoadResourceManager::getInstance()->LoadTexture(
                "../Data/Images/dirt.png");
        }
        for (auto &tree: trees) {
            int random = rand() % 2;
            if (random == 0) {
                tree->getComponent<Sprite>()->texture = LoadResourceManager::getInstance()->LoadTexture(
                    "../Data/Images/treeSmall.png");
            } else {
                tree->getComponent<Sprite>()->texture = LoadResourceManager::getInstance()->LoadTexture(
                    "../Data/Images/treeLarge.png");
            }
        }
    }
    if (themeIndex == 1) {
        for (auto &background: backGrounds) {
            background->getComponent<Sprite>()->texture = LoadResourceManager::getInstance()->LoadTexture(
                "../Data/Images/sand.png");
        }
        for (auto &tree: trees) {
            int random = rand() % 2;
            if (random == 0) {
                tree->getComponent<Sprite>()->texture = LoadResourceManager::getInstance()->LoadTexture(
                    "../Data/Images/treeBrown_large.png");
            } else {
                tree->getComponent<Sprite>()->texture = LoadResourceManager::getInstance()->LoadTexture(
                    "../Data/Images/treeBrown_small.png");
            }
        }
    }
}

std::vector<std::pair<std::string, int> > GameplayService::GetLeaderBoard() const {
    // Create a packet to notify the server
    ActionStatePacket packet;
    packet.type = 5;
    packet.id = NetworkTracking::id;

    boost::system::error_code error;

    if (NetworkReceiver::receivingEnabled) {
        NetworkReceiver::receivingEnabled = false;
    }

    // Send the request to the server
    boost::asio::write(NetworkReceiver::tcpSocket, boost::asio::buffer(&packet, sizeof(ActionStatePacket)), error);

    if (error) {
        std::cerr << "Failed to send packet: " << error.message() << std::endl;
        return {};
    }

    // Set the socket to blocking mode
    NetworkReceiver::tcpSocket.non_blocking(false);

    // Receive the size of the leaderboard
    int size;
    boost::asio::read(NetworkReceiver::tcpSocket, boost::asio::buffer(&size, sizeof(size)), error);

    if (error) {
        std::cerr << "Failed to receive leaderboard size: " << error.message() << std::endl;
        // Set the socket back to non-blocking mode
        NetworkReceiver::tcpSocket.non_blocking(true);
        return {};
    }

    std::vector<std::pair<std::string, int> > leaderboard(size);

    // Receive the leaderboard data
    for (int i = 0; i < size; ++i) {
        int usernameLength;
        boost::asio::read(NetworkReceiver::tcpSocket, boost::asio::buffer(&usernameLength, sizeof(usernameLength)),
                          error);

        if (error) {
            std::cerr << "Failed to receive username length: " << error.message() << std::endl;
            // Set the socket back to non-blocking mode
            NetworkReceiver::tcpSocket.non_blocking(true);
            NetworkReceiver::receivingEnabled = true;
            return {};
        }

        std::vector<char> usernameBuffer(usernameLength);
        boost::asio::read(NetworkReceiver::tcpSocket, boost::asio::buffer(usernameBuffer.data(), usernameLength),
                          error);

        if (error) {
            std::cerr << "Failed to receive username: " << error.message() << std::endl;
            // Set the socket back to non-blocking mode
            NetworkReceiver::tcpSocket.non_blocking(true);
            NetworkReceiver::receivingEnabled = true;
            return {};
        }

        std::string username(usernameBuffer.begin(), usernameBuffer.end());
        int point;
        boost::asio::read(NetworkReceiver::tcpSocket, boost::asio::buffer(&point, sizeof(point)), error);

        if (error) {
            std::cerr << "Failed to receive points: " << error.message() << std::endl;
            // Set the socket back to non-blocking mode
            NetworkReceiver::tcpSocket.non_blocking(true);
            NetworkReceiver::receivingEnabled = true;
            return {};
        }

        leaderboard[i] = {username, point};
    }

    // Set the socket back to non-blocking mode
    NetworkReceiver::tcpSocket.non_blocking(true);
    NetworkReceiver::receivingEnabled = true;
    return leaderboard;
}
