#include <Player.hpp>

Player::Player(float dt, sf::Vector2u screen_size)
: Entity(dt, screen_size)
{
    float y_position = static_cast<float>(screen_size.y)*0.8f;
    float x_position = static_cast<float>(screen_size.x)*0.5f; 
    m_position = sf::Vector2f(x_position, y_position);
    m_velocity = sf::Vector2f(0, 0);
    m_speed =  250;
    m_shape_vector = sf::Vector2f(100, 100);

    // calculate position limits of player
    sf::Vector2f half_size = m_shape_vector / 2.f;

    m_lower_postion_bound = half_size;
    m_upper_postion_bound = sf::Vector2f(
        static_cast<float>(screen_size.x),
        static_cast<float>(screen_size.y)
    ) - half_size;
}

Player::~Player()
{
}