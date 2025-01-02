#include <string>
#include <vector>
#include <unordered_map>
#include <mutex>
#include "room_manager.h"
#include <algorithm>
#include <map>

using namespace std;

// Add a new room to the system and assign the master role to the creator
bool RoomManager::createRoom(const string &roomName, const string &passwordHash)
{
    lock_guard<std::mutex> lock(roomMutex); // Updated to use roomMutex

    // Check if room already exists
    if (findRoom(roomName))
    {
        return false;
    }

    // Create a new room and add it to the map
    Room newRoom;
    newRoom.roomName = roomName;
    newRoom.passwordHash = passwordHash;
    newRoom.gameStarted = false;
    newRoom.mapIndex = 1;

    // Add the new room to the map
    rooms[roomName] = newRoom;

    return true;
}

// Add a player to a room as a normal player
int RoomManager::addPlayerToRoom(const string &roomName, const string &password, const Player &player)
{
    lock_guard<mutex> lock(roomMutex); // Updated to use roomMutex

    auto it = rooms.find(roomName);
    if (it != rooms.end())
    {
        if (it->second.passwordHash != password)
        {
            return 0; // Return -1 if the password is incorrect
        }
        it->second.players.push_back(player); // Add player to the room
        return 1;
    }

    return -1;
}

int RoomManager::removePlayerFromRoom(const std::string &roomName, const std::string &password, const std::string &userName)
{
    std::lock_guard<std::mutex> lock(roomMutex); // Ensure thread safety

    // Find the room by name
    auto it = rooms.find(roomName);
    if (it != rooms.end())
    {
        // Check if the password matches
        if (it->second.passwordHash != password)
        {
            return 0; // Incorrect password
        }

        auto &players = it->second.players; // Access the players in the room
        auto playerIt = std::find_if(players.begin(), players.end(), [&userName](const Player &player)
                                     {
                                         return player.username == userName; // Assuming Player has a `username` property
                                     });

        if (playerIt != players.end())
        {
            bool wasMaster = (playerIt->role == PlayerRole::MASTER); // Check if the removed player was the master
            players.erase(playerIt);                                 // Remove the player

            // if (players.empty()) {
            //     // If no players are left, destroy the room
            //     rooms.erase(it);
            //     return 3; // Room destroyed
            // }

            if (wasMaster)
            {
                // Assign the master role to another player in the room
                players.front().role = PlayerRole::MASTER;
            }

            return 1; // Player removed successfully
        }

        return 2; // Player not found in the room
    }

    return -1; // Room not found
}

// Get a list of players in a room based on room ID
vector<Player> RoomManager::getPlayersInRoom(string roomName)
{
    lock_guard<std::mutex> lock(roomMutex); // Updated to use roomMutex

    vector<Player> playerList;

    // Iterate through rooms to find the room by roomId
    for (const auto &roomPair : rooms)
    {
        if (roomPair.second.roomName == roomName)
        {
            playerList = roomPair.second.players; // Get the players from the room
            break;
        }
    }

    return playerList;
}

bool RoomManager::findRoom(string roomName)
{
    auto it = rooms.find(roomName);
    if (it != rooms.end())
    {
        return true;
    }

    return false;
}

// Retrieve the player ID based on their name, room name, and room password
int RoomManager::getPlayerId(const std::string &playerName, const std::string &roomName, const std::string &roomPassword)
{
    std::lock_guard<std::mutex> lock(roomMutex); // Ensure thread safety

    // Find the room by name
    auto it = rooms.find(roomName);
    if (it != rooms.end())
    {
        // Check if the password matches
        if (it->second.passwordHash != roomPassword)
        {
            return -1; // Incorrect password
        }

        // Search for the player in the room
        auto &players = it->second.players;
        auto playerIt = std::find_if(players.begin(), players.end(), [&playerName](const Player &player)
                                     {
                                         return player.username == playerName; // Assuming Player has a `username` property
                                     });

        if (playerIt != players.end())
        {
            return playerIt->id; // Assuming Player has an `id` property
        }

        return -2; // Player not found in the room
    }

    return -3; // Room not found
}

int RoomManager::updatePlayerStatus(const string &roomName, const string &password, const string &playerName, bool isReady, boost::asio::ip::tcp::socket *r_socket)
{
    std::lock_guard<std::mutex> lock(roomMutex); // Ensure thread safety

    // Find the room by name
    auto it = rooms.find(roomName);
    if (it == rooms.end())
    {
        return -1; // Room not found
    }

    // Check if the password matches
    if (it->second.passwordHash != password)
    {
        return 0; // Incorrect password
    }

    // Search for the player in the room
    auto &players = it->second.players;
    auto playerIt = find_if(players.begin(), players.end(), [&playerName](const Player &player)
                            {
                                return player.username == playerName; // Assuming Player has a `username` property
                            });

    if (playerIt == players.end())
    {
        return -2; // Player not found in the room
    }

    // Update the player's readiness status
    playerIt->isReady = isReady;
    playerIt->socket = r_socket;
    return 1; // Status updated successfully
}

int RoomManager::startGame(const string &roomName, const string &password, const int mapIndex)
{
    lock_guard<mutex> lock(roomMutex); // Ensure thread safety

    auto it = rooms.find(roomName);
    if (it == rooms.end())
    {
        return -1; // Room not found
    }

    if (it->second.passwordHash != password)
    {
        return 0; // Incorrect password
    }

    // Logic to start the game
    // Example: Set a "game started" flag or perform necessary initializations
    it->second.gameStarted = true;
    it->second.mapIndex = mapIndex;

    return 1; // Game successfully started
}

// Add this function to the RoomManager class
int RoomManager::getRoomStatus(const string &roomName)
{
    lock_guard<mutex> lock(roomMutex); // Ensure thread safety

    auto it = rooms.find(roomName);
    if (it == rooms.end())
    {
        return -1; // Room not found
    }

    return it->second.gameStarted ? 1 : 0;
}

int RoomManager::getRoomMapIndex(const string &roomName)
{
    lock_guard<mutex> lock(roomMutex); // Ensure thread safety

    auto it = rooms.find(roomName);
    if (it == rooms.end())
    {
        return -1; // Room not found
    }

    return it->second.mapIndex;
}
