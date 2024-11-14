#include "menu.h"
#include "../engine/engine.h"
#include "../engine/renderer.h"
#include "../appconfig.h"
#include "../type.h"
#include "../app_state/game.h"

#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

// Default constructor with login_phase = true
Menu::Menu() : Menu(true) {}  // Delegates to the second constructor

// Constructor that accepts a login_phase parameter
Menu::Menu(bool login_phase) : m_login_phase(login_phase), m_username(""), m_password(""), m_menu_index(0)
{
    // Log the value of login_phase
    std::cout << "Menu constructor called. login_phase = " << (m_login_phase ? "true" : "false") << std::endl;

    // Initialize menu items based on login phase
    if (m_login_phase) {
        m_menu_texts = {"Username", "Password", "Login", "Register", "Exit"};
    } else {
        m_menu_texts = {"1 Player", "2 Players", "Logout", "Exit"};
    }

    std::cout << "Game is still ongoing. Returning Menu state" << std::endl;

    // Setup tank pointer (selection indicator)
    m_tank_pointer = new Player(0, 0, ST_PLAYER_1);
    m_tank_pointer->direction = D_RIGHT;
    m_tank_pointer->pos_x = 120;  // Adjusted for left positioning
    m_tank_pointer->pos_y = (m_menu_index + 1) * 32 + 112;
    m_tank_pointer->setFlag(TSF_LIFE);
    m_tank_pointer->update(0);
    m_tank_pointer->clearFlag(TSF_LIFE);
    m_tank_pointer->clearFlag(TSF_SHIELD);
    m_tank_pointer->setFlag(TSF_MENU);
    m_finished = false;
}



Menu::~Menu()
{
    delete m_tank_pointer;
}

void Menu::handleLRL(int b) {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Socket creation error" << std::endl;
        return;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Connect to server
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address/ Address not supported" << std::endl;
        return;
    }

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Connection Failed" << std::endl;
        return;
    }

    if (b == 1) {
        std::string request = "LOGIN " + m_username + " " + m_password;
        send(sock, request.c_str(), request.size(), 0);
        read(sock, buffer, BUFFER_SIZE);

        if (strcmp(buffer, "SUCCESS") == 0) {
            std::cout << "Login successful" << std::endl;
            m_menu_texts = {"1 Player", "2 Players", "Logout", "Exit"};
            m_login_phase = false;
            m_menu_index = 0; // Reset the index to the first option
        } else if (strcmp(buffer, "WRONG_PASSWORD") == 0) {
            std::cout << "Incorrect password. Try again." << std::endl;
        } else if (strcmp(buffer, "USER_NOT_FOUND") == 0) {
            std::cout << "User does not exist." << std::endl;
        }
    } else if (b == 2) {
        std::string request = "REGISTER " + m_username + " " + m_password;
        send(sock, request.c_str(), request.size(), 0);
        read(sock, buffer, BUFFER_SIZE);

        if (strcmp(buffer, "REGISTERED") == 0) {
            std::cout << "Registration successful" << std::endl;
            m_menu_texts = {"1 Player", "2 Players", "Logout", "Exit"};
            m_login_phase = false;
            m_menu_index = 0; // Reset the index to the first option
        } else if (strcmp(buffer, "USERNAME_TAKEN") == 0) {
            std::cout << "Username is already taken." << std::endl;
        }
    } else if (b == 3) {
        std::string request = "LOGOUT " + m_username;
        send(sock, request.c_str(), request.size(), 0);
        read(sock, buffer, BUFFER_SIZE);

        if (strcmp(buffer, "LOGOUT_SUCCESS") == 0) {
            std::cout << "Logout successful" << std::endl;
            m_login_phase = true;  // Switch to login phase
            m_menu_texts = {"Username", "Password", "Login", "Register", "Exit"};
            m_username.clear();  // Clear stored username and password
            m_password.clear();
        } else {
            std::cout << "Logout failed. Try again." << std::endl;
        }

        close(sock);
    } else {
        std::cerr << "Invalid option" << std::endl;
    }

    close(sock);
}

void Menu::draw()
{
    Renderer* renderer = Engine::getEngine().getRenderer();
    renderer->clear();

    renderer->drawRect(&AppConfig::map_rect, {0, 0, 0, 255}, true);
    renderer->drawRect(&AppConfig::status_rect, {0, 0, 0, 255}, true);

    // Draw logo
    const SpriteData* logo = Engine::getEngine().getSpriteConfig()->getSpriteData(ST_TANKS_LOGO);
    SDL_Rect dst = {(AppConfig::map_rect.w + AppConfig::status_rect.w - logo->rect.w)/2, 50, logo->rect.w, logo->rect.h};
    renderer->drawObject(&logo->rect, &dst);

    int i = 0;
    SDL_Point text_start;
    for (const auto& text : m_menu_texts) {
        int x = (AppConfig::map_rect.w + AppConfig::status_rect.w - text.size() * 16) / 2;
        text_start = { x, (i + 1) * 32 + 120};
        std::string display_text = text;
        
        // Mask password input
        if (m_login_phase && text == "Password") {
            display_text = "Password: " + std::string(m_password.size(), '*');
        } else if (m_login_phase && text == "Username") {
            display_text = "Username: " + m_username;
        }
        
        renderer->drawText(&text_start, display_text, {255, 255, 255, 255}, 2);
        i++;
    }

    m_tank_pointer->draw();
    renderer->flush();
}

void Menu::update(Uint32 dt)
{
    m_tank_pointer->speed = m_tank_pointer->default_speed;
    m_tank_pointer->stop = true;
    m_tank_pointer->update(dt);
}

void Menu::eventProcess(SDL_Event *ev)
{
    if (ev->type == SDL_KEYDOWN)
    {
        if (ev->key.keysym.sym == SDLK_UP)
        {
            m_menu_index--;
            if (m_menu_index < 0)
                m_menu_index = m_menu_texts.size() - 1;

            m_tank_pointer->pos_y = (m_menu_index + 1) * 32 + 110;
        }
        else if (ev->key.keysym.sym == SDLK_DOWN)
        {
            m_menu_index++;
            if (m_menu_index >= m_menu_texts.size())
                m_menu_index = 0;

            m_tank_pointer->pos_y = (m_menu_index + 1) * 32 + 110;
        }
        else if (ev->key.keysym.sym == SDLK_BACKSPACE)
        {
            if (m_login_phase) {
                if (m_menu_index == 0 && !m_username.empty()) m_username.pop_back();
                else if (m_menu_index == 1 && !m_password.empty()) m_password.pop_back();
            }
        }
        else if (ev->key.keysym.sym == SDLK_RETURN)
        {
            if (m_login_phase) {
                if (m_menu_index == 2) // Login selected
                {
                    if (!m_username.empty() && !m_password.empty()) {
                        handleLRL(1); // Login selected (true for login)
                    }
                } 
                else if (m_menu_index == 3) // Register selected
                {
                    if (!m_username.empty() && !m_password.empty()) {
                        handleLRL(2); // Register selected (false for registration)
                    }
                }
                else if (m_menu_index == 4) // Exit selected
                {
                    m_finished = true;
                }
            }
            else {
                if (m_menu_index == 2) { // Logout selected in game
                    handleLRL(3); // Logout selected
                } else {
                    m_finished = true;  // Exit selected in game
                }
            }
        }
        else if (ev->key.keysym.sym == SDLK_ESCAPE)
        {
            m_menu_index = -1;
            m_finished = true;
        }
    }
    else if (ev->type == SDL_TEXTINPUT && m_login_phase)
    {
         if (m_menu_index == 0 && m_username.size() < 6) {
            m_username += ev->text.text; // Username field, limit to 6 characters
        } else if (m_menu_index == 1 && m_password.size() < 6) {
            m_password += ev->text.text; // Password field, limit to 6 characters
        }
    }
}

bool Menu::finished() const
{
    return m_finished;
}

AppState* Menu::nextState()
{
    if (m_login_phase) {
        // Still in login phase, keep the menu state
        return this;
    }

    if (m_menu_index == m_menu_texts.size() - 1 && !m_login_phase)
        return nullptr;
    else if (m_menu_index == 0)
        return new Game(1);
    else if (m_menu_index == 1)
        return new Game(2);
    return nullptr;
}
