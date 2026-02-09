#pragma once
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
};

class Game
{
private:
    GameState m_state = GameState::Menu;
    DetectedKeys m_detected_keys;
    Screen m_screen = Screen();
    bool m_quit_flag = false;
    void SetQuitFlag();

public:
    Game();
    ~Game();
    void GameLoop();
    void DetectInput();
    void HandleState();
    void Display();
    bool GetQuitFalg();
};