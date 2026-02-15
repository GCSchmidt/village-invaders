#pragma once
#include <Entity.hpp>
#include <Bullet.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <string>

class Screen
{
private:
    const sf::Font m_font = sf::Font("assests/Press_Start_2P/PressStart2P.ttf");
    std::string m_display_text;
    sf::RenderWindow& m_window;

public:
    Screen(sf::RenderWindow& window);
    ~Screen();
    void SetDisplayText(std::string);
    void WriteText();
    void DisplayMenu();
    void DisplayPause();
    void DisplayGame(float play_time);
    void DisplayEntity(const Entity& entity);
    void DisplayPlayer(const Entity& entity);
    void DisplayEnemy(const Entity& entity);
    void DisplayBullet(const Bullet& bullet);
};