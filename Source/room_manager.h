// room_manager.h

#ifndef ROOM_MANAGER_H
#define ROOM_MANAGER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <mutex>
#include <boost/asio.hpp>

using namespace std;

enum class PlayerRole
{
    MASTER,
    NORMAL
};

struct Player
{
    int id;
    string username;
    PlayerRole role;
    bool isReady;
    boost::asio::ip::tcp::socket *socket;
};

struct Room
{
    string roomName;
    string passwordHash;
    vector<Player> players;
    bool gameStarted;
    int mapIndex;
};

class RoomManager
{
public:
    bool createRoom(const string &roomName, const string &passwordHash);
    int addPlayerToRoom(const string &roomName, const string &password, const Player &player);
    int removePlayerFromRoom(const string &roomName, const string &password, const string &userName);
    vector<Player> getPlayersInRoom(string roomName);
    bool findRoom(string roomName);
    int getPlayerId(const std::string &playerName, const std::string &roomName, const std::string &roomPassword);
    int updatePlayerStatus(const string &roomName, const string &password, const string &playerName, bool isReady, boost::asio::ip::tcp::socket *socket);
    int startGame(const string &roomName, const string &password, const int mapIndex);
    int getRoomStatus(const string &roomName);
    int getRoomMapIndex(const string &roomName);

private:
    unordered_map<string, Room> rooms;
    mutex roomMutex;
};

#endif // ROOM_MANAGER_H