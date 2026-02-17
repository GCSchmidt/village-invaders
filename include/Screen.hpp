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
    std::string m_center_text;
    std::string m_hud_text;
    sf::RenderWindow& m_window;
    sf::Texture m_player_texture = sf::Texture("assests/wizard.png");
    sf::Texture m_enemy_texture = sf::Texture("assests/monster.png");
    sf::Texture m_bullet_texture = sf::Texture("assests/fire_ball.png");
    sf::Sprite m_player_sprite = sf::Sprite(m_player_texture);
    sf::Sprite m_enemy_sprite = sf::Sprite(m_enemy_texture);
    sf::Sprite m_bullet_sprite = sf::Sprite(m_bullet_texture);

public:
    Screen(sf::RenderWindow& window);
    ~Screen();
    void SetCenterText(std::string);
    void SetHudText(std::string);
    void WriteCenterText();
    void WriteHudText();
    void DisplayMenu();
    void DisplayPause();
    void DisplayLost();
    void DisplayVictory();
    void DisplayGame(float play_time);
    void DisplayEntity(const Entity& entity);
    void DisplayPlayer(const Entity& entity);
    void DisplayEnemy(const Entity& entity);
    void DisplayBullet(const Bullet& bullet);
    void DisplayLine(float m_lose_line_position_y);
};