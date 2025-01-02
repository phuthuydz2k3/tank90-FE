#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include "appstate.h"
#include <boost/asio.hpp>
#include "../objects/player.h"

using namespace std;

enum class PlayerRole {
    MASTER,
    NORMAL
};

class PlayerRoom {

public:
    int id;
    string username;
    PlayerRole role;
    bool isReady;

    PlayerRoom() : username(""), isReady(false) {}
    PlayerRoom(const string& name, bool ready) : username(name), isReady(ready) {}
    PlayerRoom(const int& id, const string& username, const PlayerRole& role, const bool& isReady) : id(id), username(username), role(role), isReady(isReady) {}
};

class Room : public AppState {
public:
    Room(string roomName, string playerName, string roomPassword, bool isOwner);
    ~Room();

    void initializeSocket();
    void draw();
    void update(Uint32 dt);
    void eventProcess(SDL_Event* ev);
    bool finished() const;
    AppState* nextState();
    void parsePlayersResponse(const string& response);
    void leaveRoom();
    void updateStatus();
    void sendStartGame(int mapIndex);

private:
    void drawPlayerList();
    void drawLeaveButton();
    bool allPlayersReady() const;
    void loadRoomFromServer();
    void startGame(int mapIndex);
    void Update();
    void Init(string& playerName, string& roomName, string& roomPassword, int mapIndex);

    string selectedMap;
    bool isOwner;
    bool playerIsReady;
    string roomPassword;
    string playerName;
    Player* r_tank_pointer;
    int r_index = 0;
    string roomName;
    vector<PlayerRoom> players;
    bool r_finished = false;
    boost::asio::io_service io_service;  // Declared as a class member
    boost::asio::ip::tcp::socket r_socket;
};

#endif
