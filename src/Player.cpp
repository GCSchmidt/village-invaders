#include <Player.hpp>

Player::Player(float dt, sf::Vector2u screen_size)
: Entity(dt, screen_size)
{
    Reset();
    m_shape_vector = sf::Vector2f(25, 25);
    m_min_shot_period = 500;                                        // minimum time between shots
    m_forward_vector = sf::Vector2f(0, -1);
    SetPositionBounds();
}

Player::~Player()
{
}


void Player::Reset()
{
    float y_position = static_cast<float>(m_screen_size.y)*0.9f;
    float x_position = static_cast<float>(m_screen_size.x)*0.5f; 
    m_position = sf::Vector2f(x_position, y_position);
    m_velocity = sf::Vector2f(0, 0);
    m_speed =  500;
    m_last_shot_time = -1;
}
