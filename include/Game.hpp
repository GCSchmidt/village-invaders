#pragma once
#include <vector>
#include <algorithm>
#include <Bullet.hpp>
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
    bool space = false;
};

class Game
{
private:
    const float m_dt = 0.01f;                                        // delta time in seconds
    const sf::Vector2u m_window_size = sf::Vector2u(1200, 800);
    bool m_quit_flag = false;
    float m_play_time;
    GameState m_state = GameState::Menu;
    DetectedKeys m_detected_keys;
    sf::RenderWindow m_window;
    Screen m_screen;
    Player m_player;
    std::vector<Bullet> m_bullets;
    sf::Clock m_clock;
    void SetQuitFlag();
    bool GetQuitFalg();
    void DetectInput();
    void HandleState();
    void HandlePlayerInput();
    void HandlePlayerMovement();
    void HanldeShooting();
    void Display();
    void UpdateEntityLocations();
    void IsOutOfBounds(sf::Vector2f position);

public:
    Game();
    ~Game();
    void GameLoop();
};