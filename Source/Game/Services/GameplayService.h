//
// Created by TCT on 11/25/2024.
//

#ifndef GAMEPLAYSERVICE_H
#define GAMEPLAYSERVICE_H
#include <functional>
#include <string>

class GameplayService {
public:
    void LoadMap(int mapIndex) const;
    void outGame() const;
    std::function<void()> onWinGame;
    std::function<void()> onLoseGame;


private:
    std::string dataPath = "../Data/MapData/map.csv";
};


#endif //GAMEPLAYSERVICE_H
