#include <Enemy.hpp>

Enemy::Enemy(
    float dt, 
    sf::Vector2u screen_size, 
    uint8_t row, 
    uint8_t col,
    uint8_t n_enemies,
    uint8_t n_enemies_per_row
)
    : Character(dt, screen_size)
{
    // set properties of enemy
    m_shape_vector = sf::Vector2f(35, 35);          
    m_min_shot_period = 1000;                                        // minimum time between shots
    m_forward_vector = sf::Vector2f(0, 1);
    m_health_points = 1;
    m_speed =  300;
    m_velocity = m_speed * sf::Vector2f(1, 0);

    // determine position and bound
    SetOffset(n_enemies_per_row);
    SetMaxXDisplacement();
    m_initial_position = CalculateInitialPostion(row, col);
    SetPositionBounds();
    m_position = m_initial_position;
}

Enemy::~Enemy()
{
}

void Enemy::SetOffset(uint8_t n_enemies_per_row)
{
    m_offset.y = 75;
    m_offset.x = m_screen_size.x / (n_enemies_per_row + 1);  // to have evenly spaced enemies
}

void Enemy::SetMaxXDisplacement()
{
    sf::Vector2f half_size = m_shape_vector / 2.f;
    m_max_x_displacement = m_offset.x - half_size.x;
}

sf::Vector2f Enemy::CalculateInitialPostion(uint8_t row, uint8_t col)
{
    sf::Vector2f initial_postion;

    initial_postion.x = col * m_offset.x;
    initial_postion.y = row * m_offset.y;

    return initial_postion;
}

void Enemy::SetPositionBounds()
{
    m_lower_postion_bound = sf::Vector2f(m_initial_position.x-m_max_x_displacement, 0.f);
    m_upper_postion_bound = sf::Vector2f(
        (m_initial_position.x + m_max_x_displacement),
        static_cast<float>(m_screen_size.y)
    );
}

void Enemy::UpdatePosition()
{
    Entity::UpdatePosition(true);
    float x_displacement = std::abs(m_position.x - m_initial_position.x);
    if (x_displacement >= m_max_x_displacement)
    {
        MoveDown(10);
        SwitchDirection();
    }
}

void Enemy::SwitchDirection()
{
    SetVelocity(-m_velocity);
}

void Enemy::MoveDown(float shift)
{
    m_position.y += shift;
}