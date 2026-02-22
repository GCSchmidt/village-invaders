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

sf::Vector2f Entity::GetVelocity() const
{
    return m_velocity;
}

void Entity::SetVelocity(sf::Vector2f velocity)
{
    m_velocity = velocity;
}

sf::Vector2f Entity::GetPosition() const
{
    return m_position;
}

void Entity::SetPostion(sf::Vector2f position)
{
    m_position = position;
}

float Entity::GetSpeed() const
{
    return m_speed;
}

sf::Vector2f Entity::GetTopLeftCorner() const
{
    return m_position - m_shape_vector/2.f;
}

sf::FloatRect Entity::GetBoundingBox() const
{
    sf::FloatRect bounding_box;
    bounding_box.position = GetTopLeftCorner();
    bounding_box.size = m_shape_vector; 
    return bounding_box;
}

sf::Vector2f Entity::GetShapeVecor() const
{
    return m_shape_vector;
}

sf::Vector2f Entity::GetForwardVector() const
{   
    return m_forward_vector;
}

void Entity::UpdateVelocity(sf::Vector2f change)
{
    m_velocity += change;
}

void Entity::UpdatePosition(bool clamp)
{
    sf::Vector2f shift = m_velocity * m_dt;
    m_position += shift;
    if (clamp)
    {
        m_position.x = std::clamp(m_position.x, m_lower_postion_bound.x, m_upper_postion_bound.x);
        m_position.y = std::clamp(m_position.y, m_lower_postion_bound.y, m_upper_postion_bound.y);
    }
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
