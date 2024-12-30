#ifndef MENU_H
#define MENU_H

#include "appstate.h"
#include "../objects/player.h"
#include <boost/asio.hpp>
#include <vector>
#include <string>

using namespace std;

class Menu : public AppState
{
public:
    Menu();
    Menu(bool login_phase);
    Menu(bool login_phase, const string& username);
    ~Menu();

    void handleLRL(int option);  // Handles login, register, create room, find room, and logout actions.
    bool finished() const;       // Returns whether the menu action is finished.
    void draw();                 // Draws the menu on the screen.
    void update(Uint32 dt);      // Updates the menu state.
    void eventProcess(SDL_Event* ev);  // Processes input events.
    AppState* nextState();       // Returns the next app state (such as game or room).

private:
    void initializeSocket();  // Initializes the socket for communication with the server.

    bool m_login_phase;                  // Flag to indicate if the menu is in login phase.
    int m_menu_index;                    // The index of the currently selected menu option.
    Player* m_tank_pointer;              // A pointer to the player (tank) object used in the menu.
    bool m_finished;                     // Flag to indicate if the menu operation is finished.
    string m_username;              // Username entered by the user.
    string m_password;              // Password entered by the user.
    string m_roomname;
    bool m_is_logged_in;                 // Flag to track if the user is logged in.
    bool m_is_entering_username;         // Flag to track if the user is entering the username.
    vector<string> m_menu_texts;  // The list of texts displayed on the menu.

    boost::asio::io_service io_service;  // io_service for boost::asio networking.
    boost::asio::ip::tcp::socket m_socket;  // Socket for network communication.
};

#endif // MENU_H
