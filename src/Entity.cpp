#include <Entity.hpp>
#include <algorithm>

Entity::Entity(float dt, sf::Vector2u screen_size)
{
    m_dt = dt;
    m_screen_size = screen_size;
}

Entity::~Entity()
{
}

uint8_t Entity::GetHealthPoints() const
{
    return m_health_points;
}

sf::Vector2f Entity::GetTopLeftCorner() const
{
    return m_position - m_shape_vector/2.f;
}

int32_t Entity::GetMinShotPeriod() const
{
    return m_min_shot_period;
}

sf::Vector2f Entity::GetPosition() const
{
    return m_position;
}

sf::Vector2f Entity::GetNewBulletPosition() const
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

sf::Vector2f Entity::GetForwardVector() const
{   
    return m_forward_vector;
}

sf::Vector2f Entity::GetShapeVecor() const
{
    return m_shape_vector;
}

bool Entity::CheckIfDead() const
{
    return (m_health_points <= 0);
}

void Entity::UpdatePosition()
{
    sf::Vector2f shift = m_velocity * m_dt;
    sf::Vector2f new_position = m_position + shift;

    new_position.x = std::clamp(new_position.x, m_lower_postion_bound.x, m_upper_postion_bound.x);
    new_position.y = std::clamp(new_position.y, m_lower_postion_bound.y, m_upper_postion_bound.y);

    m_position = new_position;
}

void Entity::SetPositionBounds()
{
    sf::Vector2f half_size = m_shape_vector / 2.f;

    m_lower_postion_bound = half_size;
    m_upper_postion_bound = sf::Vector2f(
        static_cast<float>(m_screen_size.x),
        static_cast<float>(m_screen_size.y)
    ) - half_size;
}

void Entity::SetVelocity(sf::Vector2f velocity)
{
    m_velocity = velocity;
}

float Entity::GetSpeed() const
{
    return m_speed;
}

void Entity::UpdateVelocity(sf::Vector2f change)
{
    m_velocity += change;
}