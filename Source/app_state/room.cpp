#include "room.h"
#include "../engine/renderer.h"
#include "../engine/engine.h"
#include <iostream>
#include "../appconfig.h"
#include <boost/asio.hpp>
#include <boost/asio/placeholders.hpp>
#include "menu.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "ECS/Entity/EntityManager.h"
#include "ECS/System/SystemManager.h"
#include "Game/Manager/LoadResourceManager.h"
#include "Game/Common/Time.h"
#include "Game/Services/GameplayService.h"
#include "Game/Systems/NetworkTrackingSystem.h"
#include "Game/Manager/UIManager.h"
#include "Game/Common/Event.h"
#include <SDL2/SDL_ttf.h>

using boost::asio::ip::tcp;

#define PORT 8083
#define BUFFER_SIZE 1024

using namespace std;

Room::Room(string roomName, string playerName, string roomPassword, bool isOwner) 
    : roomName(roomName), playerName(playerName), roomPassword(roomPassword), isOwner(isOwner),
      r_socket(io_service)
{
    initializeSocket();

    r_tank_pointer = new Player(0, 0, ST_PLAYER_1);
    r_tank_pointer->direction = D_RIGHT;
    r_tank_pointer->pos_x = 35;
    r_tank_pointer->pos_y = 360;
    r_tank_pointer->setFlag(TSF_LIFE);
    r_tank_pointer->update(0);
    r_tank_pointer->clearFlag(TSF_LIFE);
    r_tank_pointer->clearFlag(TSF_SHIELD);
    r_tank_pointer->setFlag(TSF_MENU);
    r_index = 0;
    r_finished = false;
    playerIsReady = false;
}

void Room::initializeSocket() {
    if (r_socket.is_open()) return;

    try {
        tcp::resolver resolver(io_service);
        tcp::resolver::query query("127.0.0.1", to_string(PORT));
        tcp::endpoint endpoint = *resolver.resolve(query);
        r_socket.connect(endpoint);

    } catch (const boost::system::system_error& e) {
        cerr << "Socket initialization error: " << e.what() << endl;
    }
}

void Room::loadRoomFromServer() {
    vector<char> buffer(BUFFER_SIZE);
    boost::system::error_code ec;
    string request = "GET_PLAYERS " + roomName;
    boost::asio::write(r_socket, boost::asio::buffer(request), ec);

    if (ec) {
        cerr << "Error writing to socket: " << ec.message() << endl;
        return;
    }

    // Set a deadline timer to handle potential hangs
    boost::asio::deadline_timer timer(io_service);
    timer.expires_from_now(boost::posix_time::seconds(5));
    bool timed_out = false;

    // Timeout handler
    timer.async_wait([&](const boost::system::error_code& err) {
        if (!err) {
            timed_out = true;
            r_socket.close(); // Force the socket to close on timeout
        }
    });

    size_t totalBytesRead = 0;
    r_socket.non_blocking(true);
    try {
        while (true) {
            size_t bytesRead = r_socket.read_some(boost::asio::buffer(buffer), ec);

            if (ec == boost::asio::error::eof || bytesRead == 0) {
                cerr << "Connection closed by server or no data: " << ec.message() << endl;
                return;
            } else if (ec) return;

            totalBytesRead += bytesRead;

            // Check if the buffer contains the complete message (use a delimiter if necessary)
            string response(buffer.begin(), buffer.begin() + totalBytesRead);
            if (response.find("PLAYERS_IN_ROOM") != string::npos) {
                timer.cancel();
                parsePlayersResponse(response);
                return;
            } else if (response.find("START_GAME_SIGNAL") != string::npos) {
                timer.cancel();
                startGame();
                return;
            }

            // Ensure buffer isn't overrun
            if (totalBytesRead >= BUFFER_SIZE) {
                cerr << "Buffer overflow detected while reading server response." << endl;
                return;
            }
        }
    } catch (const boost::system::system_error& e) {
        cerr << "Error during communication with server: " << e.what() << endl;
    }

    if (timed_out) {
        cerr << "Socket operation timed out." << endl;
    }
}

void Room::parsePlayersResponse(const string& response) {
    vector<PlayerRoom> newPlayers;

    size_t firstSpace = response.find(" ");
    if (firstSpace == string::npos || response.substr(0, firstSpace) != "PLAYERS_IN_ROOM") {
        cerr << "Invalid response format: " << response << endl;
        return;
    }

    istringstream response_stream(response.substr(firstSpace + 1));
    int id;
    string username;
    string role;
    string playerIsReady;

    while (response_stream >> id >> username >> role >> playerIsReady) {
        bool rready = playerIsReady == "READY" ? true : false;

        PlayerRoom player;

        auto it = find_if(players.begin(), players.end(), [id](const PlayerRoom& player) {
            return player.id == id;
        });

        if (it != players.end()) {
            if (playerName == it->username) {
                if (role == "MASTER") {
                    isOwner = true;
                    it->role = PlayerRole::MASTER;
                    it->isReady = true;
                }
            } else {
                it->id = id;
                it->username = username;
                it->role = (role == "MASTER" ? PlayerRole::MASTER : PlayerRole::NORMAL);
                it->isReady = rready;
            }
            player = *it;
        } else {
            player = PlayerRoom(id, username, 
            (role == "MASTER" ? PlayerRole::MASTER : PlayerRole::NORMAL), rready);
        }

        newPlayers.push_back(player);
    }

    players = newPlayers;
}

void Room::leaveRoom() {
    string message = "LEAVE_ROOM " + playerName + " " + roomName + " " + roomPassword;
    boost::asio::write(r_socket, boost::asio::buffer(message));
    boost::system::error_code ec;
    vector<char> buffer(BUFFER_SIZE);

    try {
        size_t bytesRead = r_socket.read_some(boost::asio::buffer(buffer), ec);
        if (ec == boost::asio::error::eof || bytesRead == 0) {
            cerr << "Error reading from socket: " << ec.message() << endl;
        }
        // Convert the response into a string for easy comparison
        string response(buffer.begin(), buffer.end());
        response = response.substr(0, response.find('\0'));  // Null-terminate properly
        
        cout << "Response: " << response << endl;
        
        if (response == "LEFT_ROOM") {
            cout << "Left room." << endl;
            r_finished = true;
        } else if (response == "ROOM_NOT_FOUND") {
            cout << "Room not found." << endl;
        } else if (response == "WRONG_PASSWORD") {
            cout << "Wrong password." << endl;
        } else if (response == "USER_NOT_IN_ROOM"){
            cout << "User not in room." << endl;
        } else {
            cerr << "Invalid response: " << response << endl;
        }
    } catch (const boost::system::system_error& e) {
        cerr << "Error reading from socket: " << e.what() << endl;
    }
}

void Room::draw() {
    loadRoomFromServer();

    // std::vector<char> buffer(1024); // Adjust buffer size as needed
    // r_socket.non_blocking(true);
    // while (true) {
    //     boost::system::error_code ec;
    //     size_t bytesRead = r_socket.read_some(boost::asio::buffer(buffer), ec);

    //     if (ec) {
    //         if (ec == boost::asio::error::eof) {
    //             // std::cout << "Connection closed by server." << std::endl;
    //             break; // Exit the loop on end of file (connection closed)
    //         } else {
    //             // std::cerr << "Error while reading: " << ec.message() << std::endl;
    //             break; // Exit on any other error
    //         }
    //     }

    //     if (bytesRead > 0) {
    //         std::string response(buffer.begin(), buffer.begin() + bytesRead);
    //         if (response == "START_GAME_SIGNAL") {
    //             std::cout << "Start game signal received from server." << std::endl;
    //             // Call startGame or perform necessary action
    //             startGame();
    //         } else {
    //             std::cout << "Not start game: " + response << std::endl;
    //         }
    //     } else {
    //         std::cout << "No data received. Exiting loop." << std::endl;
    //         break; // Exit loop if no data is received
    //     }
    // }

    Renderer* renderer = Engine::getEngine().getRenderer();
    renderer->clear();

    renderer->drawRect(&AppConfig::room_rect, {0, 0, 0, 255}, true);
    renderer->drawRect(&AppConfig::status_room_rect, {0, 0, 0, 255}, true);

    const SpriteData* logo = Engine::getEngine().getSpriteConfig()->getSpriteData(ST_TANKS_LOGO);
    SDL_Rect dst = {(AppConfig::map_rect.w + AppConfig::status_rect.w - logo->rect.w) / 2, 50, logo->rect.w, logo->rect.h};
    renderer->drawObject(&logo->rect, &dst);

    SDL_Point titlePosition = {70, 140};
    renderer->drawText(&titlePosition, "Room: " + roomName, {255, 255, 255, 255}, 2);

    drawPlayerList();
    drawLeaveButton();
    r_tank_pointer->draw();

    renderer->flush();
}

void Room::drawPlayerList() {
    Renderer* renderer = Engine::getEngine().getRenderer();
    int y_offset = 200;

    for (size_t i = 0; i < players.size(); ++i) {
        SDL_Point textPosition = {70, y_offset + i * 40};
        std::string playerInfo = std::to_string(players[i].id) + ". " + players[i].username + "  | " + (players[i].role == PlayerRole::MASTER ? "Master" : "Normal");
        renderer->drawText(&textPosition, playerInfo, {255, 255, 255, 255}, 2); // Font size reduced to 1
        string status = (players[i].role == PlayerRole::MASTER ? "|   Ready  " : (players[i].isReady ? "|   Ready  " : "| Not Ready"));
        SDL_Point textPosition2 = {playerIsReady ? 300 : 275, y_offset + i * 40};
        renderer->drawText(&textPosition2, status, {255, 255, 255, 255}, 2);
    }
}

void Room::drawLeaveButton() {
    Renderer* renderer = Engine::getEngine().getRenderer();
    SDL_Point textPosition = {300, 370};
    SDL_Point textPosition2 = {70, 370};
    SDL_Point textPosition3 = {325, 170};
    renderer->drawText(&textPosition, "Leave Room", {255, 255, 255, 255}, 2);
    renderer->drawText(&textPosition2, (isOwner ? "Start Game" : (playerIsReady ? "Not Ready" : "Ready")), {255, 255, 255, 255}, 2);
    renderer->drawText(&textPosition3, "Status", {255, 255, 255, 255}, 2);
    SDL_Point textPosition4 = {190, 170};
    renderer->drawText(&textPosition4, "Role", {255, 255, 255, 255}, 2); // Font size reduced to 1
}

void Room::updateStatus() {
    // Check if the socket is open
    if (!r_socket.is_open()) {
        cerr << "Socket is not open, cannot update status." << endl;
        return;
    }

    try {
        // Create the message to send to the server
        string statusMessage = "UPDATE_STATUS " + playerName + " " + roomName + " " + roomPassword + " " + (playerIsReady ? "READY" : "NOT_READY");
        
        // Send the message to the server
        boost::asio::write(r_socket, boost::asio::buffer(statusMessage));
        
        // Wait for the server's response
        vector<char> buffer(BUFFER_SIZE);
        boost::system::error_code ec;
        size_t bytesRead = r_socket.read_some(boost::asio::buffer(buffer), ec);

        if (ec == boost::asio::error::eof || bytesRead == 0) {
            cerr << "Connection closed by server or no data received: " << ec.message() << endl;
            return;
        }

        // Convert the response into a string for processing
        string response(buffer.begin(), buffer.begin() + bytesRead);

        if (response == "STATUS_UPDATED") {
            cout << "Player status successfully updated." << endl;
        } else {
            cerr << "Failed to update status: " << response << endl;
        }
    } catch (const boost::system::system_error& e) {
        cerr << "Error updating status: " << e.what() << endl;
    }
}


void Room::eventProcess(SDL_Event* ev) {
    if (ev->type == SDL_KEYDOWN) {
        if (ev->key.keysym.sym == SDLK_RETURN) {
            if (r_index == 0) {
                auto it = find_if(players.begin(), players.end(), [&](const PlayerRoom& player) {
                    return player.username == this->playerName;
                });
                if (it != players.end()) {
                    if (it->role == PlayerRole::NORMAL) {
                        it->isReady = !it->isReady;
                        playerIsReady = it->isReady;
                        updateStatus();
                    } else {
                        if (allPlayersReady()) {
                            sendStartGame();
                            startGame();
                        }
                    }
                } else {
                    cout << "Not found player name: " + playerName << endl;
                }
            } else if (r_index == 1) {
                leaveRoom();
            }
        } else if (ev->key.keysym.sym == SDLK_LEFT) {
            r_index--;
            if (r_index < 0) {
                r_index = 1;
            }

            r_tank_pointer->pos_x = 35 + r_index * 230;
        } else if (ev->key.keysym.sym == SDLK_RIGHT) {
            r_index++;
            if (r_index > 1) {
                r_index = 0;
            }

            r_tank_pointer->pos_x = 30 + r_index * 230;
        }
    }
}

bool Room::finished() const {
    return r_finished;
}

bool Room::allPlayersReady() const {
    for (const auto& player : players) {
        cout << player.username << " " << player.isReady << endl;
        if (!player.isReady) return false;
    }
    return true;
}

void Room::Init(string& playerName, string& roomName, string& roomPassword) {
     if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL haven't been initialized: " << SDL_GetError() << std::endl;
        return;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "SDL_image haven't been initialized: " << IMG_GetError() << std::endl;
        SDL_Quit();
        return;
    }
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return;
    }
    if (TTF_Init() < 0) {
        std::cerr << "Failed to initialize SDL_ttf: " << TTF_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
        std::cerr << "Failed to initialize SDL_mixer: " << Mix_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    LoadResourceManager::getInstance()->InitWindow();
    SystemManager::getInstance()->init(playerName, roomName, roomPassword);
    UIManager::getInstance()->Init();
    GameplayService().LoadMap(1);
    GameplayService().EnterGame();
}

void Room::sendStartGame() {
    // Check if the socket is open
    if (!r_socket.is_open()) {
        cerr << "Socket is not open, cannot send start game request." << endl;
        return;
    }

    try {
        // Create the message to send to the server
        string startGameMessage = "START_GAME " + roomName + " " + roomPassword;
        
        // Send the message to the server
        boost::asio::write(r_socket, boost::asio::buffer(startGameMessage));
        
        // Wait for the server's response
        vector<char> buffer(BUFFER_SIZE);
        boost::system::error_code ec;
        size_t bytesRead = r_socket.read_some(boost::asio::buffer(buffer), ec);

        if (ec == boost::asio::error::eof || bytesRead == 0) {
            cerr << "Connection closed by server or no data received: " << ec.message() << endl;
            return;
        }

        // Convert the response into a string for processing
        string response(buffer.begin(), buffer.begin() + bytesRead);
        cout << "Server response: " << response << endl;

        if (response == "GAME_STARTED") {
            cout << "Game successfully started." << endl;
        } else {
            cerr << "Failed to start game: " << response << endl;
        }
    } catch (const boost::system::system_error& e) {
        cerr << "Error sending start game request: " << e.what() << endl;
    }
}


void Room::startGame() {
    delete r_tank_pointer;
    if (r_socket.is_open()) {
        r_socket.close();
    }

    // Init(playerName, roomName, roomPassword);
    // bool running = true;
    // SDL_Event event;
    // Uint32 lastTime = SDL_GetTicks();
    // while (running) {
    //     Uint32 currentTime = SDL_GetTicks();
    //     Time::deltaTime = (currentTime - lastTime) / 1000.0f;
    //     lastTime = currentTime;
    //     while (SDL_PollEvent(&event)) {
    //         if (event.type == SDL_QUIT) {
    //             running = false;
    //         }
    //     }
    //     Update();
    //     SDL_Delay(16);
    // }

    // LoadResourceManager::getInstance()->CleanUp();
    // EntityManager::getInstance()->clearEntities();

    Init(playerName, roomName, roomPassword);
    bool running = true;
    Uint32 lastTime = SDL_GetTicks();
    while (running) {
        Uint32 currentTime = SDL_GetTicks();
        Time::deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;
        while (SDL_PollEvent(&Event::event)) {
            if (Event::event.type == SDL_QUIT) {
                running = false;
            }
        }
        Update();
        SDL_Delay(16);
    }
    GameplayService().outGame();
    LoadResourceManager::getInstance()->CleanUp();
    EntityManager::getInstance()->clearEntities();
}

void Room::Update()
{
    SDL_SetRenderDrawColor(LoadResourceManager::getInstance()->GetRenderer(), 0, 0, 0, 255);
    SystemManager::getInstance()->update();
    EntityManager::getInstance()->lateUpdate();
    SDL_RenderPresent(LoadResourceManager::getInstance()->GetRenderer());
    SDL_RenderClear(LoadResourceManager::getInstance()->GetRenderer());
}

AppState* Room::nextState() {
    if (r_index == 0) {
        return nullptr;
    } else if (r_index == 1) {
        Menu* menu = new Menu(false, playerName);
        return menu;
    }
}

void Room::update(Uint32 dt) {
    r_tank_pointer->speed = r_tank_pointer->default_speed;
    r_tank_pointer->stop = true;
    r_tank_pointer->update(dt);
}

Room::~Room() {
    delete r_tank_pointer;
    if (r_socket.is_open()) {
        r_socket.close();
    }
}
