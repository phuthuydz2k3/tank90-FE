#include "menu.h"
#include "room.h"
#include "../engine/engine.h"
#include "../engine/renderer.h"
#include "../appconfig.h"
#include "../type.h"

#include <iostream>
#include <boost/asio.hpp>
#include <array>

#define PORT 8083
#define BUFFER_SIZE 1024

using boost::asio::ip::tcp;

using namespace std;

Menu::Menu() : Menu(true) {}

Menu::Menu(bool login_phase)
    : m_login_phase(login_phase),
      m_menu_index(0),
      m_tank_pointer(nullptr),
      m_finished(false),
      m_username(""),
      m_password(""),
      m_roomname(""),
      m_is_logged_in(false),
      m_is_entering_username(true),
      m_socket(io_service) {  // Initialize io_service for boost::asio

    initializeSocket();

    m_menu_texts = m_login_phase 
        ? vector<string>{"Username", "Password", "Login", "Register", "Exit"}
        : vector<string>{"Roomname", "Password", "Create Room", "Find Room", "Logout", "Exit"};

    m_tank_pointer = new Player(0, 0, ST_PLAYER_1);
    m_tank_pointer->direction = D_RIGHT;
    m_tank_pointer->pos_x = 120;
    m_tank_pointer->pos_y = (m_menu_index + 1) * 32 + 112;
    m_tank_pointer->setFlag(TSF_LIFE);
    m_tank_pointer->update(0);
    m_tank_pointer->clearFlag(TSF_LIFE);
    m_tank_pointer->clearFlag(TSF_SHIELD);
    m_tank_pointer->setFlag(TSF_MENU);
    m_finished = false;
}

Menu::Menu(bool login_phase, const string& username)
    : m_login_phase(login_phase),
      m_menu_index(0),
      m_tank_pointer(nullptr),
      m_finished(false),
      m_username(username),
      m_password(""),
      m_roomname(""),
      m_is_logged_in(false),
      m_is_entering_username(true),
      m_socket(io_service) {  // Initialize io_service for boost::asio

    initializeSocket();

    m_menu_texts = m_login_phase 
        ? vector<string>{"Username", "Password", "Login", "Register", "Exit"}
        : vector<string>{"Roomname", "Password", "Create Room", "Find Room", "Logout", "Exit"};

    m_tank_pointer = new Player(0, 0, ST_PLAYER_1);
    m_tank_pointer->direction = D_RIGHT;
    m_tank_pointer->pos_x = 120;
    m_tank_pointer->pos_y = (m_menu_index + 1) * 32 + 112;
    m_tank_pointer->setFlag(TSF_LIFE);
    m_tank_pointer->update(0);
    m_tank_pointer->clearFlag(TSF_LIFE);
    m_tank_pointer->clearFlag(TSF_SHIELD);
    m_tank_pointer->setFlag(TSF_MENU);
    m_finished = false;
}

Menu::~Menu() {
    delete m_tank_pointer;
    if (m_socket.is_open()) {
        m_socket.close();
    }
}

void Menu::initializeSocket() {
    if (m_socket.is_open()) return;

    cout << "I'm here" << endl;

    try {
        tcp::resolver resolver(io_service);
        tcp::resolver::query query("127.0.0.1", to_string(PORT));
        tcp::endpoint endpoint = *resolver.resolve(query);
        m_socket.connect(endpoint);
    } catch (const boost::system::system_error& e) {
        cerr << "Socket initialization error: " << e.what() << endl;
    }
}

void Menu::handleLRL(int option) {
    vector<char> buffer(BUFFER_SIZE);
    string request;

    if (!m_socket.is_open()) {
        cerr << "Socket is not initialized. Exiting." << endl;
        return;
    }

    // Build request string based on the option
    switch (option) {
        case 1:  // Login
            request = "LOGIN " + m_username + " " + m_password;
            break;
        case 2:  // Register
            request = "REGISTER " + m_username + " " + m_password;
            break;
        case 4:  // Create Room
            request = "CREATE_ROOM " + m_username + " " + m_roomname + " " + m_password;
            break;
        case 5:  // Find Room
            request = "JOIN_ROOM " + m_username + " " + m_roomname + " " + m_password;
            break;
        case 3:  // Logout
            request = "LOGOUT " + m_username;
            break;
        default:
            cerr << "Invalid option" << endl;
            return;
    }

    // Write request to the server
    boost::asio::write(m_socket, boost::asio::buffer(request));
    boost::system::error_code ec;

    try {
        printf("Handling option %d\n", option);
        size_t bytesRead = m_socket.read_some(boost::asio::buffer(buffer), ec);
        if (ec == boost::asio::error::eof || bytesRead == 0) {
            cerr << "Error reading from socket: " << ec.message() << endl;
        }
        // Convert the response into a string for easy comparison
        string response(buffer.begin(), buffer.end());
        response = response.substr(0, response.find('\0'));  // Null-terminate properly
        
        cout << "Response: " << response << endl;
        // Handle the response based on the option
        if (option == 1) {  // Login
            if (response == "SUCCESS") {
                cout << "Login successful" << endl;
                m_menu_texts = {"Roomname", "Password", "Create Room", "Find Room", "Logout", "Exit"};
                m_login_phase = false;
                m_password.clear();
                m_menu_index = 0;
                m_tank_pointer->pos_y = (m_menu_index + 1) * 32 + 110;
            } else if (response == "WRONG_PASSWORD") {
                cout << "Incorrect password. Try again." << endl;
            } else if (response == "USER_NOT_FOUND") {
                cout << "User does not exist." << endl;
            }
        } else if (option == 2) {  // Register
            if (response == "REGISTERED") {
                cout << "Registration successful" << endl;
                m_menu_texts = {"Roomname", "Password", "Create Room", "Find Room", "Logout", "Exit"};
                m_login_phase = false;  // Clear username and password
                m_password.clear();
                m_menu_index = 0;
                m_tank_pointer->pos_y = (m_menu_index + 1) * 32 + 110;
            } else if (response == "USERNAME_TAKEN") {
                cout << "Username is already taken." << endl;
            }
        } else if (option == 3) {  // Logout
            if (response == "LOGOUT_SUCCESS") {
                cout << "Logout successful" << endl;
                m_login_phase = true;
                m_menu_texts = {"Username", "Password", "Login", "Register", "Exit"};
                m_username.clear();
                m_password.clear();
                m_menu_index = 0;
                m_tank_pointer->pos_y = (m_menu_index + 1) * 32 + 110;
            } else {
                cout << "Logout failed" << endl;
            }
        } else if (option == 4) {
            if (response.find("ROOM_CREATED") == 0) {
                cout << "Room created successfully" << endl;
                m_finished = true;
            } else if (response == "ROOM_EXISTS") {
                cout << "Room already exists." << endl;
            }
        }
        else if (option == 5) {  // Find Room
            if (response == "JOINED_ROOM") {
                cout << "Joined Room." << endl;
                m_finished = true;
            } else if (response == "ROOM_NOT_FOUND") {
                cout << "Room not found." << endl;
            } else {
                cout << "Wrong password." << endl;
            }
        } else {
            cerr << "Invalid option" << endl;
        }

    } catch (const boost::system::system_error& e) {
        cerr << "Error reading from socket: " << e.what() << endl;
    }
}


void Menu::draw() {
    Renderer* renderer = Engine::getEngine().getRenderer();
    renderer->clear();

    renderer->drawRect(&AppConfig::map_rect, {0, 0, 0, 255}, true);
    renderer->drawRect(&AppConfig::status_rect, {0, 0, 0, 255}, true);

    const SpriteData* logo = Engine::getEngine().getSpriteConfig()->getSpriteData(ST_TANKS_LOGO);
    SDL_Rect dst = {(AppConfig::map_rect.w + AppConfig::status_rect.w - logo->rect.w)/2, 50, logo->rect.w, logo->rect.h};
    renderer->drawObject(&logo->rect, &dst);

    int i = 0;
    SDL_Point text_start;
    for (const auto& text : m_menu_texts) {
        int x = (AppConfig::map_rect.w + AppConfig::status_rect.w - text.size() * 16) / 2;
        text_start = { x, (i + 1) * 32 + 120};
        string display_text = text;

        if (text == "Password") {
            display_text = "Password: " + string(m_password.size(), '*');
        } else if (m_login_phase && text == "Username") {
            display_text = "Username: " + m_username;
        } else if (!m_login_phase && text == "Roomname") {
            display_text = "Roomname: " + m_roomname;
        }

        renderer->drawText(&text_start, display_text, {255, 255, 255, 255}, 2);
        i++;
    }

    m_tank_pointer->draw();
    renderer->flush();
}

void Menu::update(Uint32 dt) {
    m_tank_pointer->speed = m_tank_pointer->default_speed;
    m_tank_pointer->stop = true;
    m_tank_pointer->update(dt);
}

void Menu::eventProcess(SDL_Event* ev) {
    if (ev->type == SDL_KEYDOWN) {
        if (ev->key.keysym.sym == SDLK_UP) {
            m_menu_index--;
            if (m_menu_index < 0)
                m_menu_index = (int) m_menu_texts.size() - 1;

            m_tank_pointer->pos_y = (m_menu_index + 1) * 32 + 110;
        } else if (ev->key.keysym.sym == SDLK_DOWN) {
            m_menu_index++;
            if (m_menu_index >= (int) m_menu_texts.size())
                m_menu_index = 0;

            m_tank_pointer->pos_y = (m_menu_index + 1) * 32 + 110;
        } else if (ev->key.keysym.sym == SDLK_BACKSPACE) {
            if (m_login_phase) {
                if (m_menu_index == 0 && !m_username.empty()) m_username.pop_back();
                else if (m_menu_index == 1 && !m_password.empty()) m_password.pop_back();
            } else {
                if (m_menu_index == 0 && !m_roomname.empty()) m_roomname.pop_back();
                else if (m_menu_index == 1 && !m_password.empty()) m_password.pop_back();
            }
        } else if (ev->key.keysym.sym == SDLK_RETURN) {
            if (m_login_phase) {
                if (m_menu_index == 2) {
                    if (!m_username.empty() && !m_password.empty()) {
                        handleLRL(1); // Login
                    }
                } else if (m_menu_index == 3) {
                    if (!m_username.empty() && !m_password.empty()) {
                        handleLRL(2); // Register
                    }
                } else if (m_menu_index == 4) {
                    m_finished = true;
                }
            } else {
                if (m_menu_index == 2) {
                    if (!m_username.empty() && !m_password.empty()) {
                        handleLRL(4);
                    }
                } else if (m_menu_index == 3) {
                    if (!m_username.empty() && !m_password.empty()) {
                        handleLRL(5);
                    }
                } else if (m_menu_index == 4) {
                    handleLRL(3); // Logout
                } else if (m_menu_index == 5) {
                    m_finished = true;
                }
            }
        } else if (ev->key.keysym.sym == SDLK_ESCAPE) {
            m_menu_index = -1;
            m_finished = true;
        }
    } else if (ev->type == SDL_TEXTINPUT) {
        if (m_login_phase) {
            if (m_menu_index == 0 && m_username.size() < 6) {
                m_username += ev->text.text;
            } else if (m_menu_index == 1 && m_password.size() < 6) {
                m_password += ev->text.text;
            }
        } else {
            if (m_menu_index == 0 && m_roomname.size() < 6) {
                m_roomname += ev->text.text;
            } else if (m_menu_index == 1 && m_password.size() < 6) {
                m_password += ev->text.text;
            }
        }
    }
}

bool Menu::finished() const {
    return m_finished;
}

AppState* Menu::nextState() {
    if (m_login_phase) return this;  // Stay in the menu if login phase is active

    // Check for exit conditions
    if (m_menu_index == (int)(m_menu_texts.size() - 1) && !m_login_phase) {
        return nullptr;  // Exit the application if the last option is selected
    }

    else if (m_menu_index == 2) { 
        if (m_socket.is_open()) {
            m_socket.close();
        }
        Room* room = new Room(m_roomname, m_username, m_password, true);
        return room;
    }
    else if (m_menu_index == 3) {
        if (m_socket.is_open()) {
            m_socket.close();
        }
        Room* room = new Room(m_roomname, m_username, m_password, false);
        return room;
    }

    return nullptr;
}

