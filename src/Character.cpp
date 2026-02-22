#include <Character.hpp>
#include <algorithm>

Character::Character(float dt, sf::Vector2u screen_size)
: Entity(dt, screen_size)
{
    m_dt = dt;
    m_screen_size = screen_size;
}

Character::~Character()
{
}

uint8_t Character::GetHealthPoints() const
{
    return m_health_points;
}

int32_t Character::GetMinShotPeriod() const
{
    return m_min_shot_period;
}

sf::Vector2f Character::GetNewBulletPosition() const
{   
    sf::Vector2f bullet_postion;
    bullet_postion.x = m_position.x;
    sf::Vector2f half_shape = m_shape_vector/2.f;
    sf::Vector2f shift;
    shift.x = half_shape.x * m_forward_vector.x;
    shift.y = half_shape.y * m_forward_vector.y;
    bullet_postion = m_position + shift;
    return bullet_postion;
}

bool Character::CheckIfDead() const
{
    return (m_health_points <= 0);
}

bool Character::UpdateLastShotTime(int32_t current_shot_time)
{
    int32_t shot_period = current_shot_time - m_last_shot_time;    
    if ( shot_period > m_min_shot_period)
    {
        m_last_shot_time = current_shot_time;
        return true;
    }
    return false;
}

void Character::Hit(uint8_t damage)
{
    m_health_points -= damage;
}