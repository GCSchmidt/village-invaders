#include <Bullet.hpp>

Bullet::Bullet(float dt, sf::Vector2f position, sf::Vector2f forward_vector, BulletSource source, sf::Vector2u screen_size)
: Entity(dt, screen_size)
{
    m_dt = dt;
    m_position = position;
    m_forward_vector = forward_vector;
    m_source = source;
    m_shape_vector = sf::Vector2f(25, 25);
    m_screen_size = screen_size;
    m_speed = 1000; 
    m_velocity = m_speed * m_forward_vector;
}

Bullet::~Bullet()
{
}

void Bullet::UpdatePosition()
{
    Entity::UpdatePosition(false);
    DetermineOutOfBounds();
}

void Bullet::DetermineOutOfBounds()
{
    sf::Vector2f half_size = m_shape_vector / 2.f;
    sf::Vector2f  m_lower_postion_bound = sf::Vector2f(0,0) - half_size;
    sf::Vector2f m_upper_postion_bound = sf::Vector2f(
        static_cast<float>(m_screen_size.x),
        static_cast<float>(m_screen_size.y)
    ) + half_size;

    bool left_check = (m_position.x < m_lower_postion_bound.x);
    bool right_check = (m_position.x > m_upper_postion_bound.x);
    bool top_check = (m_position.y < m_lower_postion_bound.y);
    bool bottom_check = (m_position.y > m_upper_postion_bound.y);

    if (left_check || right_check || top_check || bottom_check)
    {
        m_out_of_bounds = true;
    }
    else
    {
        m_out_of_bounds = false;
    }
}

bool Bullet::GetOutOfBounds() const
{
    return m_out_of_bounds;
}

bool Bullet::GetCollided() const
{
    return m_collided;
}

void Bullet::Hit()
{
    m_collided = true;
}

uint8_t Bullet::GetDamage() const
{
    return m_damage;
}