#pragma once
#include <vector>
#include <algorithm>
#include <Bullet.hpp>
#include <Player.hpp>
#include <Enemy.hpp>
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
    Lost,
    Victory,
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
    const uint8_t m_n_enemies_per_row = 10;
    const sf::Vector2u m_window_size = sf::Vector2u(1600, 1000);
    uint8_t m_n_enemies;                                       // number of alive enemies
    float m_play_time;
    float m_lose_line_position_y = m_window_size.y * 0.8f;
    GameState m_state = GameState::Menu;
    DetectedKeys m_detected_keys;
    sf::RenderWindow m_window;
    Screen m_screen;
    Player m_player;
    std::vector<Bullet> m_bullets;
    std::vector<Enemy> m_enemies;
    sf::Clock m_clock;

    void SetupGame();
    void DetectInput();
    void HandleState();
    void HandlePlayerInput();
    void HandlePlayerMovement();
    void HanldePlayerShooting();
    void Display();
    void DisplayBullets();
    void DisplayEnemies();
    void UpdateSpriteLocations();
    void RemoveBulletsOutOfBounds();
    void CreateEnemies(uint8_t n_enemies);
    void RemoveAllEnemies();
    void RemoveAllBullets();
    void RemoveDeadEnemies();
    void CheckIfLost();
    void CheckIfVictory();
    void PlayLoop();
    void DetectHits();
    bool DetectCollision(sf::FloatRect bounding_box_1, sf::FloatRect bounding_box_2);

public:
    Game();
    ~Game();
    void GameLoop();
};