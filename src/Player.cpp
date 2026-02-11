#include <Player.hpp>

Player::Player(float dt, sf::Vector2u screen_size)
: Entity(dt, screen_size)
{
    float y_position = static_cast<float>(screen_size.y)*0.8f;
    float x_position = static_cast<float>(screen_size.x)*0.5f; 
    m_position = sf::Vector2f(x_position, y_position);
    m_velocity = sf::Vector2f(0, 0);
}

Player::~Player()
{
}