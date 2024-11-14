#ifndef MENU_H
#define MENU_H

#include "appstate.h"
#include "../objects/player.h"

#include <vector>
#include <string>

/**
 * @brief
 * Klasa wyboru trybu gry: logowanie, 1 gracz, 2 graczy lub wyjście. Klasa jest pierwszym stanem aplikacji, pojawia się zaraz po uruchomieniu programu i pozwala na przejście do stanu gry (klasa Game) po zalogowaniu.
 */
class Menu : public AppState
{
public:
    Menu();
    Menu(bool login_phase);  // New constructor declaration
    ~Menu();

    void handleLRL(int b);

    /**
     * Funkcja sprawdzająca czy należy zakończyć stan menu i przejści do kolejnego stanu gry.
     * @return @a true jeżeli została wybrana, któraś z opcji menu lub został wciśnięty kalwisz Esc, @a false w przeciwnym wypadku
     */
    bool finished() const;

    /**
     * Funkcja rysuje logo gry, napisy menu i wskaźnik wybranej pozycji w kształcie czołgu.
     */
    void draw();

    /**
     * Funkcja odpowiada za animację wskaźnika w postaci czołgu.
     * @param dt - czas od ostatniej animacji
     * @see Tank::update(Uint32 dt)
     */
    void update(Uint32 dt);

    /**
     * Funkcja odpowiada na reakcję na klawisze:
     * @li Strzałka w górę i w dół - zmiana wybranej pozycji menu
     * @li Enter i Spacja - zatwierdzenie obecnej pozycji menu
     * @li Esc - wyjście z programu
     * @param ev - wskaźnik na unię SDL_Event przechowującą typ i parametry różnych zdarzeń
     */
    void eventProcess(SDL_Event* ev);

    /**
     * Przejście do gry w wybranym trybie lub wyjście z aplikacji.
     * @return @a nullptr jeżeli wybrano "Exit" lub wciśnięto Esc, w przeciwnym wypadku funkcja zwraca wskaźnik na Game
     */
    AppState* nextState();

private:
    /**
     * Kontener przechowujący wszystkie napisy jakie pojawiają się w menu.
     */
    std::vector<std::string> m_menu_texts;

    /**
     * Indeks wybranej pozycji menu.
     */
    int m_menu_index;

    /**
     * Zmienna odpowiadająca za wskaźnik w postaci czołgu.
     */
    Player* m_tank_pointer;

    /**
     * Zmienna przechowuje informację, czy należy zakończyć bieżący stan gry i przejść do gry lub wyłączyć aplikację.
     */
    bool m_finished;

    /**
     * Zmienna przechowująca aktualnie wprowadzany tekst przez użytkownika (dla logowania).
     */
    std::string m_username;
    std::string m_password;

    /**
     * Flaga określająca, czy użytkownik jest zalogowany.
     */
    bool m_is_logged_in;

    /**
     * Flaga określająca, czy aktualnie wprowadzany tekst dotyczy nazwy użytkownika (true) czy hasła (false).
     */
    bool m_is_entering_username;

    bool m_login_phase; // Added this line
};

#endif // MENU_H
