// #include <iostream>
// #include <vector>
// #include <cstring>
// #include <deque>
// #include <boost/asio.hpp>
// #include "Game/Common/TankStatePacket.h"
// #include <SDL2/SDL.h>

// #include "Game/Common/ActionStatePacket.h"

// std::vector<TankStatePacket> tankStates;
// std::deque<boost::asio::ip::tcp::socket> clientSockets;
// int nextId = 1;

// void printPacket(const TankStatePacket& packet) {
//     std::cout << "Received Packet:" << std::endl;
//     std::cout << "Position: (" << packet.positionX << ", " << packet.positionY << ")" << std::endl;
//     std::cout << "Angle: " << packet.angle << std::endl;
// }

// void handleClientOutPacket(const ActionStatePacket& packet, boost::asio::ip::tcp::socket& tcpSocket) {
//     // Remove the client from tankStates
//     tankStates.erase(std::remove_if(tankStates.begin(), tankStates.end(), [&](const TankStatePacket& tankState) {
//         return tankState.id == packet.id;
//     }), tankStates.end());

//     // Remove the client from clientSockets
//     clientSockets.erase(std::remove_if(clientSockets.begin(), clientSockets.end(), [&](const boost::asio::ip::tcp::socket& socket) {
//      return socket.remote_endpoint() == tcpSocket.remote_endpoint();
//  }), clientSockets.end());

//     std::cout << "Client " << packet.id << " removed from the game." << std::endl;
// }

// void broadcastActionStatePacket(const ActionStatePacket& packet) {
//     try {
//     for (auto& socket : clientSockets) {
//         boost::asio::write(socket, boost::asio::buffer(&packet, sizeof(ActionStatePacket)));
//     }

//     } catch (std::exception& e) {
//         // std::cerr << "Exception in broadCast: " << e.what() << std::endl;
//     }
// }

// void handleIncomingPackets(boost::asio::ip::tcp::socket& tcpSocket) {
//     try {
//         while (true) {
//             ActionStatePacket actionPacket;
//             boost::system::error_code error;
//              size_t len = tcpSocket.read_some(boost::asio::buffer(&actionPacket, sizeof(ActionStatePacket)), error);

//             if (error == boost::asio::error::eof) {
//                 break; // Connection closed cleanly by peer
//             } else if (error) {
//                 std::cout << "Receive failed: " << error.message() << std::endl;
//                 // throw boost::system::system_error(error); // Some other error
//                 continue;
//             }

//             if (len == sizeof(ActionStatePacket)) {
//                 // Broadcast the ActionStatePacket to all clients
//                 if (actionPacket.type == 1 && actionPacket.isOut) {
//                     handleClientOutPacket(actionPacket, tcpSocket);
//                 }
//                 broadcastActionStatePacket(actionPacket);
//             }
//         }
//     } catch (std::exception& e) {
//         std::cerr << "Exception in handleIncomingPackets: " << e.what() << std::endl;
//     }
// }

// void handleClient(boost::asio::ip::tcp::socket tcpSocket) {
//     try {
//         // Check if the client socket already exists in clientSockets
//         bool socketExists = false;
//         for (const auto& socket : clientSockets) {
//             if (socket.remote_endpoint() == tcpSocket.remote_endpoint()) {
//                 socketExists = true;
//                 break;
//             }
//         }
//         std::cout << socketExists << std::endl;
//         if (!socketExists) {
//             // Generate a unique ID for the client
//             int clientId = nextId++;

//             // Send the unique ID to the client
//             boost::asio::write(tcpSocket, boost::asio::buffer(&clientId, sizeof(clientId)));

//             // Initialize a tank for the client
//             TankStatePacket newTankState;
//             newTankState.id = clientId;
//             tankStates.push_back(newTankState);

//             std::cout << "Assigned ID " << clientId << " to new client" << std::endl;

//             // Add the client's socket to the list of client sockets
//             clientSockets.push_back(std::move(tcpSocket));
//             std::cout << clientSockets.size() << std::endl;
//             std::thread(handleIncomingPackets, std::ref(clientSockets.back())).detach();
//         } else {
//             std::cout << "Client already exists" << std::endl;
//         }
//     } catch (std::exception& e) {
//         std::cerr << "Exception in handleClient: " << e.what() << std::endl;
//     }
// }

// void updateTankState(const TankStatePacket& packet) {
//     for (auto& tankState : tankStates) {
//         if (tankState.id == packet.id) {
//             tankState = packet;
//             return;
//         }
//     }
//     // If tank state not found, add new tank state
//     tankStates.push_back(packet);
// }

// void broadcastTankStates(boost::asio::ip::udp::socket& socket, boost::asio::ip::udp::endpoint& broadcast_endpoint) {
//     // Calculate the total size of the packet
//     size_t packetSize = tankStates.size() * sizeof(TankStatePacket);
//     std::vector<char> buffer(packetSize);
//     std::memcpy(buffer.data(), tankStates.data(), packetSize);

//     boost::system::error_code error;
//     socket.send_to(boost::asio::buffer(buffer), broadcast_endpoint, 0, error);

//     if (error) {
//         std::cerr << "Failed to send packet: " << error.message() << std::endl;
//     } else {
//         for (const auto& tankState : tankStates) {
//             // std::cout << "Tank ID: " << tankState.id << std::endl;
//             // std::cout << "Position: (" << tankState.positionX << ", " << tankState.positionY << ")" << std::endl;
//             // std::cout << "Angle: " << tankState.angle << std::endl;
//             // if(tankState.isShooting) {
//             //     std::cout << tankStates.size() << std::endl;
//             //     std::cout << "Tank " << tankState.id << " is shooting" << std::endl;
//             // }
//         }
//     }
// }

// int main(int argc, char* argv[]) {
//     boost::asio::io_context io_context;
//     boost::asio::ip::tcp::acceptor acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 8081));
//     boost::asio::ip::udp::socket socket(io_context, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 8080));
//     boost::asio::ip::udp::endpoint sender_endpoint;
//     boost::asio::ip::udp::endpoint broadcast_endpoint(boost::asio::ip::address_v4::broadcast(), 8082);

//     socket.set_option(boost::asio::socket_base::broadcast(true));

//     std::vector<char> recv_buffer(1024);
//     Uint32 lastSendTime = SDL_GetTicks();
//     Uint32 sendInterval = 1000 / 60; // 60 FPS

//     std::thread([&acceptor]() {
//         while (true) {
//             boost::asio::ip::tcp::socket tcpSocket(acceptor.get_executor());
//             acceptor.accept(tcpSocket);
//             std::thread(handleClient, std::move(tcpSocket)).detach();
//         }
//     }).detach();

//     while (true) {
//         boost::system::error_code error;
//         size_t len = socket.receive_from(boost::asio::buffer(recv_buffer), sender_endpoint, 0, error);

//         if (error && error != boost::asio::error::message_size) {
//             std::cerr << "Receive failed: " << error.message() << std::endl;
//             continue;
//         }

//         if (len > 0) {
//             TankStatePacket receivedPacket;
//             std::memcpy(&receivedPacket, recv_buffer.data(), sizeof(TankStatePacket));
//             // printPacket(receivedPacket);

//             // Update tank state
//             updateTankState(receivedPacket);
//         }

//         Uint32 currentTime = SDL_GetTicks();
//         // Broadcast tank states at 60 FPS
//         if (currentTime - lastSendTime >= sendInterval) {
//             broadcastTankStates(socket, broadcast_endpoint);
//             lastSendTime = currentTime;
//         }

//         SDL_Delay(16);
//     }

//     return 0;
// }

#include <iostream>
#include <cstring>
#include <openssl/sha.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <libpq-fe.h>
#include <thread>
#include <mutex>
#include <unordered_map>
#include <boost/asio.hpp>
#include "room_manager.h"
#include <SDL2/SDL.h>
#include <deque>

#include "Game/Common/ActionStatePacket.h"
#include "Game/Common/TankStatePacket.h"

#define PORT 8083
#define BUFFER_SIZE 1024
#define MAX_LOGIN_ATTEMPTS 3

using namespace std;

mutex db_mutex;
mutex session_mutex;

int nextPlayerId = 1;
vector<TankStatePacket> tankStates;
std::deque<boost::asio::ip::tcp::socket> clientSockets;

// Global session map to track active logins
unordered_map<string, bool> activeSessions; // Maps username to login status (true if logged in)

// Password hashing function
string hashPassword(const string &password)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char *)password.c_str(), password.size(), hash);

    char hexStr[65];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        sprintf(hexStr + (i * 2), "%02x", hash[i]);
    }
    hexStr[64] = 0;
    return string(hexStr);
}

// Function to connect to PostgreSQL database
PGconn *connectDB()
{
    const char *conninfo = "dbname=network_programming user=postgres password=postgres hostaddr=127.0.0.1 port=5432";
    PGconn *conn = PQconnectdb(conninfo);

    if (PQstatus(conn) != CONNECTION_OK)
    {
        cerr << "Connection to database failed: " << PQerrorMessage(conn) << endl;
        PQfinish(conn);
        exit(1);
    }
    return conn;
}

bool doesUserExist(PGconn *conn, const string &username)
{
    const char *paramValues[1] = {username.c_str()};
    PGresult *res = PQexecParams(conn,
                                 "SELECT * FROM network_programming.users WHERE username = $1;",
                                 1, nullptr, paramValues, nullptr, nullptr, 0);

    bool userExists = PQntuples(res) > 0;
    PQclear(res);
    return userExists;
}

bool checkLogin(PGconn *conn, const string &username, const string &password)
{
    string passwordHash = hashPassword(password);
    const char *paramValues[2] = {username.c_str(), passwordHash.c_str()};
    PGresult *res = PQexecParams(conn,
                                 "SELECT * FROM network_programming.users WHERE username = $1 AND password_hash = $2;",
                                 2, nullptr, paramValues, nullptr, nullptr, 0);

    bool loginSuccess = PQntuples(res) > 0;
    PQclear(res);
    return loginSuccess;
}

// Register a new user
bool registerUser(PGconn *conn, const string &username, const string &password)
{
    if (doesUserExist(conn, username))
    {
        return false; // Username already exists
    }
    string passwordHash = hashPassword(password);
    const char *paramValues[2] = {username.c_str(), passwordHash.c_str()};
    PGresult *res = PQexecParams(conn,
                                 "INSERT INTO network_programming.users (username, password_hash) VALUES ($1, $2);",
                                 2, nullptr, paramValues, nullptr, nullptr, 0);

    bool registrationSuccess = PQresultStatus(res) == PGRES_COMMAND_OK;
    PQclear(res);
    return registrationSuccess;
}

RoomManager roomManager;

void handleClient(boost::asio::ip::tcp::socket socket)
{
    PGconn *conn = connectDB();

    try
    {
        while (true)
        {
            boost::system::error_code ec;
            vector<char> buffer(BUFFER_SIZE);

            // Read the incoming request (blocking)
            size_t bytesRead = socket.read_some(boost::asio::buffer(buffer), ec);

            if (ec == boost::asio::error::eof || bytesRead == 0)
            {
                cout << "Client disconnected." << endl;
                break;
            }

            // Create a string from the buffer based on the number of bytes read
            string request(buffer.begin(), buffer.begin() + bytesRead);

            if (request.starts_with("LOGIN "))
            {
                string username = request.substr(6, request.find(' ', 6) - 6);
                string password = request.substr(request.find(' ', 6) + 1);

                unique_lock<mutex> lock(db_mutex);             // Lock for thread safety
                lock_guard<mutex> session_lock(session_mutex); // Lock for session map access

                if (activeSessions.find(username) != activeSessions.end() && activeSessions[username])
                {
                    boost::asio::write(socket, boost::asio::buffer("ACCOUNT_ALREADY_LOGGED_IN"));
                    continue;
                }

                if (!doesUserExist(conn, username))
                {
                    boost::asio::write(socket, boost::asio::buffer("USER_NOT_FOUND"));
                }
                else
                {
                    int attempts = 0;
                    bool loggedIn = false;
                    while (attempts < MAX_LOGIN_ATTEMPTS && !loggedIn)
                    {
                        if (checkLogin(conn, username, password))
                        {
                            boost::asio::write(socket, boost::asio::buffer("SUCCESS"));
                            loggedIn = true;
                            activeSessions[username] = true;
                        }
                        else
                        {
                            attempts++;
                            if (attempts < MAX_LOGIN_ATTEMPTS)
                            {
                                boost::asio::write(socket, boost::asio::buffer("WRONG_PASSWORD"));
                            }
                            else
                            {
                                boost::asio::write(socket, boost::asio::buffer("LOGIN_FAILED"));
                            }
                        }
                    }
                }
            }
            else if (request.starts_with("REGISTER "))
            {
                string username = request.substr(9, request.find(' ', 9) - 9);
                string password = request.substr(request.find(' ', 9) + 1);

                unique_lock<mutex> lock(db_mutex);
                if (registerUser(conn, username, password))
                {
                    cout << "User registered: " << username << endl;
                    boost::asio::write(socket, boost::asio::buffer("REGISTERED"));
                }
                else
                {
                    boost::asio::write(socket, boost::asio::buffer("USERNAME_TAKEN"));
                }
            }
            else if (request.starts_with("LOGOUT "))
            {
                string username = request.substr(7);
                {
                    lock_guard<mutex> session_lock(session_mutex);
                    activeSessions[username] = false;
                }

                boost::asio::write(socket, boost::asio::buffer("LOGOUT_SUCCESS"));
            }
            else if (request.starts_with("CREATE_ROOM "))
            {
                string data = request.substr(12); // Length of "CREATE_ROOM "

                // Use a string stream to extract the individual parts
                istringstream iss(data);
                string userName, roomName, password;

                iss >> userName >> roomName >> password;

                if (roomManager.createRoom(roomName, password))
                {
                    Player newPlayer = {nextPlayerId++, userName, PlayerRole::MASTER, true, &socket};
                    roomManager.addPlayerToRoom(roomName, password, newPlayer);
                    cout << "Room created: " << roomName << endl;
                    boost::asio::write(socket, boost::asio::buffer("ROOM_CREATED"));
                }
                else
                {
                    boost::asio::write(socket, boost::asio::buffer("ROOM_EXISTS"));
                }
            }
            else if (request.starts_with("JOIN_ROOM "))
            {
                istringstream stream(request.substr(10)); // Loại bỏ "JOIN_ROOM "
                string userName, roomName, password;
                stream >> userName >> roomName >> password; // Đọc username và roomName từ stream
                cout << "Joining room: " << roomName << " " << password << endl;
                Player newPlayer = {nextPlayerId++, userName, PlayerRole::NORMAL, false, &socket};
                int result = roomManager.addPlayerToRoom(roomName, password, newPlayer);
                if (result == 1)
                {
                    boost::asio::write(socket, boost::asio::buffer("JOINED_ROOM"));
                }
                else if (result == -1)
                {
                    boost::asio::write(socket, boost::asio::buffer("ROOM_NOT_FOUND"));
                }
                else
                {
                    boost::asio::write(socket, boost::asio::buffer("WRONG_PASSWORD"));
                }
            }
            else if (request.starts_with("LEAVE_ROOM "))
            {
                istringstream stream(request.substr(10)); // Loại bỏ "JOIN_ROOM "
                string userName, roomName, password;
                stream >> userName >> roomName >> password; // Đọc username và roomName từ stream
                cout << "Leaving room: " << roomName << " " << password << endl;
                int result = roomManager.removePlayerFromRoom(roomName, password, userName);
                if (result == 1)
                {
                    boost::asio::write(socket, boost::asio::buffer("LEFT_ROOM"));
                }
                else if (result == -1)
                {
                    boost::asio::write(socket, boost::asio::buffer("ROOM_NOT_FOUND"));
                }
                else if (result == 0)
                {
                    boost::asio::write(socket, boost::asio::buffer("WRONG_PASSWORD"));
                }
                else
                {
                    boost::asio::write(socket, boost::asio::buffer("USER_NOT_IN_ROOM"));
                }
            }
            else if (request.starts_with("GET_PLAYERS "))
            {
                string roomName = request.substr(12);
                vector<Player> players = roomManager.getPlayersInRoom(roomName);

                if (roomManager.getRoomStatus(roomName) == 1)
                {
                    boost::asio::write(socket, boost::asio::buffer("START_GAME_SIGNAL " + to_string(roomManager.getRoomMapIndex(roomName))));
                    continue;
                }

                string response = "PLAYERS_IN_ROOM ";
                for (const Player &player : players)
                {
                    response += to_string(player.id) + " " + player.username + " " +
                                (player.role == PlayerRole::MASTER ? "MASTER" : "NORMAL") + " " + (player.isReady ? "READY" : "NOT_READY") + " ";
                }

                boost::asio::write(socket, boost::asio::buffer(response));
            }
            else if (request.starts_with("UPDATE_STATUS "))
            {
                // Process UPDATE_STATUS request
                istringstream stream(request.substr(14)); // Remove "UPDATE_STATUS "
                string playerName, roomName, password, readiness;
                stream >> playerName >> roomName >> password >> readiness;

                bool isReady = (readiness == "READY");

                // Update the player's readiness status in the room
                int result = roomManager.updatePlayerStatus(roomName, password, playerName, isReady, &socket);

                if (result == 1)
                {
                    boost::asio::write(socket, boost::asio::buffer("STATUS_UPDATED"));
                    cout << "Socket: " << playerName << " " << &socket << endl;
                    cout << "Updated status for player " << playerName << " in room " << roomName << endl;
                }
                else if (result == -1)
                {
                    boost::asio::write(socket, boost::asio::buffer("ROOM_NOT_FOUND"));
                }
                else if (result == 0)
                {
                    boost::asio::write(socket, boost::asio::buffer("WRONG_PASSWORD"));
                }
                else
                {
                    boost::asio::write(socket, boost::asio::buffer("USER_NOT_IN_ROOM"));
                }
            }
            else if (request.starts_with("START_GAME "))
            {
                istringstream stream(request.substr(11)); // Remove "START_GAME "
                string roomName, password, mapIndex;
                stream >> roomName >> password >> mapIndex;

                cout << "Starting game in room " << roomName << " with password " << password << " with mapIndex " << mapIndex << endl;
                int result = roomManager.startGame(roomName, password, stoi(mapIndex));
                if (result == 1)
                {
                    boost::asio::write(socket, boost::asio::buffer("GAME_STARTED"));

                    // // Notify all players in the room
                    // auto players = roomManager.getPlayersInRoom(roomName);
                    // for (const auto& player : players) {
                    //     if (player.role == PlayerRole::MASTER) {
                    //         continue;
                    //     }
                    //     cout << "Notifying player " << player.username << " to start game" << endl;
                    //     if (player.socket && player.socket->is_open()) { // Dereference the pointer
                    //         cout << "Sending START_GAME_SIGNAL to player " << player.username << endl;
                    //         cout << "Player socket: " << player.socket << endl;
                    //         boost::asio::write(*player.socket, boost::asio::buffer("START_GAME_SIGNAL"));

                    //     }
                    // }
                }
                else if (result == -1)
                {
                    boost::asio::write(socket, boost::asio::buffer("ROOM_NOT_FOUND"));
                }
                else if (result == 0)
                {
                    boost::asio::write(socket, boost::asio::buffer("WRONG_PASSWORD"));
                }
            }
            else
            {
                boost::asio::write(socket, boost::asio::buffer("INVALID_REQUEST"));
            }
        }
    }
    catch (const exception &e)
    {
        cerr << "Exception caught: " << e.what() << endl;
    }

    PQfinish(conn);
}

void printPacket(const TankStatePacket &packet)
{
    std::cout << "Received Packet:" << std::endl;
    std::cout << "Position: (" << packet.positionX << ", " << packet.positionY << ")" << std::endl;
    std::cout << "Angle: " << packet.angle << std::endl;
}

void updateTankState(const TankStatePacket &packet)
{
    for (auto &tankState : tankStates)
    {
        if (tankState.id == packet.id)
        {
            tankState = packet;
            return;
        }
    }
    // If tank state not found, add new tank state
    tankStates.push_back(packet);
}

void broadcastTankStates(boost::asio::ip::udp::socket &socket, boost::asio::ip::udp::endpoint &broadcast_endpoint)
{
    // Calculate the total size of the packet
    size_t packetSize = tankStates.size() * sizeof(TankStatePacket);
    std::vector<char> buffer(packetSize);
    std::memcpy(buffer.data(), tankStates.data(), packetSize);

    boost::system::error_code error;
    socket.send_to(boost::asio::buffer(buffer), broadcast_endpoint, 0, error);

    if (error)
    {
        std::cerr << "Failed to send packet: " << error.message() << std::endl;
    }
    else
    {
        for (const auto &tankState : tankStates)
        {
            // std::cout << "Tank ID: " << tankState.id << std::endl;
            // std::cout << "Position: (" << tankState.positionX << ", " << tankState.positionY << ")" << std::endl;
            // std::cout << "Angle: " << tankState.angle << std::endl;
            // if(tankState.isShooting) {
            //     std::cout << tankStates.size() << std::endl;
            //     std::cout << "Tank " << tankState.id << " is shooting" << std::endl;
            // }
        }
    }
}

void handleClientOutPacket(const ActionStatePacket &packet, boost::asio::ip::tcp::socket &tcpSocket)
{
    // Remove the client from tankStates
    tankStates.erase(std::remove_if(tankStates.begin(), tankStates.end(), [&](const TankStatePacket &tankState)
                                    { return tankState.id == packet.id; }),
                     tankStates.end());

    // Remove the client from clientSockets
    clientSockets.erase(std::remove_if(clientSockets.begin(), clientSockets.end(), [&](const boost::asio::ip::tcp::socket &socket)
                                       { return socket.remote_endpoint() == tcpSocket.remote_endpoint(); }),
                        clientSockets.end());

    std::cout << "Client " << packet.id << " removed from the game." << std::endl;
}

void handleIncreaseScorePacket(const int playerId)
{
    PGconn *conn = connectDB();
    if (PQstatus(conn) != CONNECTION_OK) {
        std::cerr << "Connection to database failed: " << PQerrorMessage(conn) << std::endl;
        PQfinish(conn);
        return;
    }

    const char *paramValues[1] = {std::to_string(playerId).c_str()};
    PGresult *res = PQexecParams(conn,
                                 "UPDATE network_programming.users SET point = point + 1 WHERE username = $1;",
                                 1, nullptr, paramValues, nullptr, nullptr, 0);

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cerr << "Failed to update score: " << PQerrorMessage(conn) << std::endl;
    } else {
        std::cout << "Score updated for player ID: " << playerId << std::endl;
    }

    PQclear(res);
    PQfinish(conn);
}

void handleGetLeaderBoard(boost::asio::ip::tcp::socket &tcpSocket) {
    PGconn *conn = connectDB();
    if (PQstatus(conn) != CONNECTION_OK) {
        std::cerr << "Connection to database failed: " << PQerrorMessage(conn) << std::endl;
        PQfinish(conn);
        return;
    }

    PGresult *res = PQexec(conn, "SELECT username, point FROM network_programming.users ORDER BY point DESC;");

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        std::cerr << "Failed to retrieve leaderboard: " << PQerrorMessage(conn) << std::endl;
        PQclear(res);
        PQfinish(conn);
        return;
    }

    int rows = PQntuples(res);
    std::vector<std::pair<std::string, int>> leaderboard;
    for (int i = 0; i < rows; ++i) {
        std::string username = PQgetvalue(res, i, 0);
        int point = std::stoi(PQgetvalue(res, i, 1));
        leaderboard.emplace_back(username, point);
    }

    PQclear(res);
    PQfinish(conn);

    // Send the size of the leaderboard
    int size = leaderboard.size();
    boost::asio::write(tcpSocket, boost::asio::buffer(&size, sizeof(size)));

    // Send the leaderboard data
    for (const auto &entry : leaderboard) {
        int usernameLength = entry.first.size();
        std::cout << "Username: " << entry.first << ", Points: " << entry.second << std::endl;
        boost::asio::write(tcpSocket, boost::asio::buffer(&usernameLength, sizeof(usernameLength)));
        boost::asio::write(tcpSocket, boost::asio::buffer(entry.first));
        boost::asio::write(tcpSocket, boost::asio::buffer(&entry.second, sizeof(entry.second)));
    }
}

void broadcastActionStatePacket(const ActionStatePacket &packet)
{
    try
    {
        for (auto &socket : clientSockets)
        {
            boost::asio::write(socket, boost::asio::buffer(&packet, sizeof(ActionStatePacket)));
        }
    }
    catch (std::exception &e)
    {
        // std::cerr << "Exception in broadCast: " << e.what() << std::endl;
    }
}

void handleIncomingPackets(boost::asio::ip::tcp::socket &tcpSocket)
{
    try
    {
        while (true)
        {
            ActionStatePacket actionPacket;
            boost::system::error_code error;
            size_t len = tcpSocket.read_some(boost::asio::buffer(&actionPacket, sizeof(ActionStatePacket)), error);

            if (error == boost::asio::error::eof)
            {
                break; // Connection closed cleanly by peer
            }
            else if (error)
            {
                std::cout << "Receive failed: " << error.message() << std::endl;
                // throw boost::system::system_error(error); // Some other error
                continue;
            }

            if (len == sizeof(ActionStatePacket))
            {
                // Broadcast the ActionStatePacket to all clients
                if (actionPacket.type == 4) {
                    handleIncreaseScorePacket(actionPacket.id);
                    continue;
                } else if (actionPacket.type == 5) {
                    handleGetLeaderBoard(tcpSocket);
                    continue;
                } else if (actionPacket.type == 1 && actionPacket.isOut)
                {
                    handleClientOutPacket(actionPacket, tcpSocket);
                }
                broadcastActionStatePacket(actionPacket);
            }
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception in handleIncomingPackets: " << e.what() << std::endl;
    }
}

void handleClient1(boost::asio::ip::tcp::socket tcpSocket)
{
    try
    {
        // Check if the client socket already exists in clientSockets
        bool socketExists = false;
        for (const auto &socket : clientSockets)
        {
            if (socket.remote_endpoint() == tcpSocket.remote_endpoint())
            {
                socketExists = true;
                break;
            }
        }
        std::cout << socketExists << std::endl;
        if (!socketExists)
        {
            // Buffer to store the incoming request
            char buffer[256];
            std::memset(buffer, 0, sizeof(buffer));

            // Read the request from the client
            size_t length = tcpSocket.read_some(boost::asio::buffer(buffer));
            std::string requestMessage(buffer, length);

            // Parse the request message (space-separated values)
            std::istringstream iss(requestMessage);
            std::string playerName, roomName, roomPassword;
            iss >> playerName >> roomName >> roomPassword;

            // Log the received details
            std::cout << "Received request from client:" << std::endl;
            std::cout << "Player Name: " << playerName << std::endl;
            std::cout << "Room Name: " << roomName << std::endl;
            std::cout << "Room Password: " << roomPassword << std::endl;

            // Attempt to retrieve the player ID from the RoomManager
            int existingPlayerId = roomManager.getPlayerId(playerName, roomName, roomPassword);

            cout << "Existing player ID: " << existingPlayerId << endl;

            if (existingPlayerId < 0)
            {
                // Handle errors based on the value of existingPlayerId
                switch (existingPlayerId)
                {
                case -1:
                    std::cerr << "Incorrect password for room: " << roomName << std::endl;
                    break;
                case -2:
                    std::cerr << "Player not found in room: " << roomName << std::endl;
                    break;
                case -3:
                    std::cerr << "Room not found: " << roomName << std::endl;
                    break;
                default:
                    std::cerr << "Unknown error occurred while retrieving player ID" << std::endl;
                    break;
                }

                // Send the error code back to the client
                boost::asio::write(tcpSocket, boost::asio::buffer(&existingPlayerId, sizeof(existingPlayerId)));
                return;
            }

            // Player exists; return their ID to the client
            boost::asio::write(tcpSocket, boost::asio::buffer(&existingPlayerId, sizeof(existingPlayerId)));

            // Initialize a tank for the client
            TankStatePacket newTankState;
            newTankState.id = existingPlayerId;
            tankStates.push_back(newTankState);

            std::cout << "Assigned ID " << existingPlayerId << " to new client: " << playerName << std::endl;

            // Add the client's socket to the list of client sockets
            clientSockets.push_back(std::move(tcpSocket));
            std::cout << clientSockets.size() << std::endl;
            std::thread(handleIncomingPackets, std::ref(clientSockets.back())).detach();
        }
        else
        {
            std::cout << "Client already exists" << std::endl;
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception in handleClient1: " << e.what() << std::endl;
    }
}

void runTcpServer1()
{
    try
    {
        boost::asio::io_context io_context;
        boost::asio::ip::tcp::acceptor acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 8081));
        boost::asio::ip::udp::socket socket(io_context, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 8080));
        boost::asio::ip::udp::endpoint sender_endpoint;
        boost::asio::ip::udp::endpoint broadcast_endpoint(boost::asio::ip::address_v4::broadcast(), 8082);

        socket.set_option(boost::asio::socket_base::broadcast(true));

        std::vector<char> recv_buffer(1024);
        Uint32 lastSendTime = SDL_GetTicks();
        Uint32 sendInterval = 1000 / 60;

        std::thread([&acceptor]()
                    {
            while (true) {
                boost::asio::ip::tcp::socket tcpSocket(acceptor.get_executor());
                acceptor.accept(tcpSocket);
                std::thread(handleClient1, std::move(tcpSocket)).detach();
            } })
            .detach();

        while (true)
        {
            boost::system::error_code error;
            size_t len = socket.receive_from(boost::asio::buffer(recv_buffer), sender_endpoint, 0, error);

            if (error && error != boost::asio::error::message_size)
            {
                std::cerr << "Receive failed: " << error.message() << std::endl;
                continue;
            }

            if (len > 0)
            {
                TankStatePacket receivedPacket;
                std::memcpy(&receivedPacket, recv_buffer.data(), sizeof(TankStatePacket));
                // printPacket(receivedPacket);

                // Update tank state
                updateTankState(receivedPacket);
            }

            Uint32 currentTime = SDL_GetTicks();
            // Broadcast tank states at 60 FPS
            if (currentTime - lastSendTime >= sendInterval)
            {
                broadcastTankStates(socket, broadcast_endpoint);
                lastSendTime = currentTime;
            }

            SDL_Delay(16);
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception in runTcpServer1: " << e.what() << std::endl;
    }
}

void runTcpServer2()
{
    try
    {
        boost::asio::io_context io_service;
        boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), PORT);
        boost::asio::ip::tcp::acceptor acceptor(io_service, endpoint);

        std::cout << "Server listening on port " << PORT << "..." << std::endl;

        while (true)
        {
            boost::asio::ip::tcp::socket socket(io_service);
            acceptor.accept(socket);
            std::thread(handleClient, std::move(socket)).detach();
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception in runTcpServer2: " << e.what() << std::endl;
    }
}

int main()
{
    // Run both servers concurrently
    std::thread server1Thread(runTcpServer1);
    std::thread server2Thread(runTcpServer2);

    // Join threads to ensure main waits for them to finish
    server1Thread.join();
    server2Thread.join();

    return 0;
}