#pragma once
#include <Player.hpp>
#include <Screen.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System.hpp>

enum class GameState
{
    Menu,
    Paused,
    Playing,
    Exit
};

struct DetectedKeys
{
    bool enter  = false;
    bool esc = false;
    bool p = false;
    bool a = false;
    bool d = false;
};

class Game
{
private:
    const float m_dt = 0.05f;                                        // delta time in seconds
    const sf::Vector2u m_window_size = sf::Vector2u(1200, 800);
    bool m_quit_flag = false;
    GameState m_state = GameState::Menu;
    DetectedKeys m_detected_keys;
    sf::RenderWindow m_window;
    Screen m_screen;
    Player m_player;
    void SetQuitFlag();
    bool GetQuitFalg();
    void DetectInput();
    void HandleState();
    void HandlePlayerInput();
    void Display();
    void UpdateEntityLocations();

public:
    Game();
    ~Game();
    void GameLoop();
};