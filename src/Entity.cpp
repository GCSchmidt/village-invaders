#include <Entity.hpp>

Entity::Entity(float dt, sf::Vector2u screen_size)
{
    m_dt = dt;
}

Entity::~Entity()
{
}

uint8_t Entity::GetHealthPoints() const
{
    return m_health_points;
}

sf::Vector2f Entity::GetPosition() const
{
    return m_position;
}

bool Entity::CheckIfDead() const
{
    return (m_health_points <= 0);
}

void Entity::UpdateLocation()
{
    // TODO
    // limit location to window boundaries
    sf::Vector2f shift = m_velocity * m_dt;
    m_position += shift;
}

void Entity::SetVelocity(sf::Vector2f velocity)
{
    m_velocity = velocity;
}

void Entity::UpdateVelocity(sf::Vector2f change)
{
    m_velocity += change;
}