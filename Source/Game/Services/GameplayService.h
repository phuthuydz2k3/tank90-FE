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

    void LoseGame() const;

    void WinGame() const;

    void EnterGame() const;

    void PauseGame(bool isPause) const;

    void NotifyServerForWinGame() const;

    std::vector<std::pair<std::string, int> > GetLeaderBoard() const;

private:
    std::string dataPath = "../Data/MapData/map.csv";
};


#endif //GAMEPLAYSERVICE_H
