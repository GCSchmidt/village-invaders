#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <string>

class Screen
{
private:
    sf::Vector2u m_window_size = sf::Vector2u(1800, 1200);
    sf::RenderWindow& m_window = sf::RenderWindow( sf::VideoMode(m_window_size), "Village Invaders" );
    std::string m_display_text;
    const sf::Font m_font = sf::Font("assests/Press_Start_2P/PressStart2P.ttf");

public:
    Screen();
    ~Screen();
    void SetDisplayText(std::string);
    sf::RenderWindow& GetWindow();
    void WriteText();
    void DisplayMenu();
    void DisplayPause();
    void DisplayGame();
};