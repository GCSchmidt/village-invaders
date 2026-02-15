#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>


enum class BulletSource
{
    Palyer,
    Enemy
};

class Bullet
{
private:

public:
    Bullet(float dt, sf::Vector2f position, sf::Vector2f forward_vector, BulletSource source, sf::Vector2u screen_size);
    ~Bullet();
    sf::Vector2f GetTopLeftCorner() const;
    sf::Vector2f GetPosition() const;
    void SetPostion();
    float GetSpeed() const;
    uint8_t GetDamage() const;
    sf::Vector2f GetShapeVecor() const;
    void UpdatePosition();
    void SetOutOfBounds();
    bool GetOutOfBounds() const;
    bool GetCollided() const;
    float GetRadius() const;
    void Hit();
    sf::FloatRect Bullet::GetBoundingBox() const;

protected:
    float m_dt;
    float m_radius = 5.0f;
    uint8_t m_damage = 1;
    sf::Vector2f m_position;        // center of Bullet
    float m_speed = 1000;                  // size of velocity 
    bool m_out_of_bounds = false;       // check if bullet is of screen
    bool m_collided = false;              // check if bullett has hot anythings and should be destroyed
    sf::Vector2f m_forward_vector;  //   
    BulletSource m_source;
    sf::Vector2f m_velocity;        // change in location per frame
    sf::Vector2f m_shape_vector = sf::Vector2f(m_radius*2, m_radius*2);
    sf::Vector2u m_screen_size;
    sf::Vector2f m_lower_postion_bound;
    sf::Vector2f m_upper_postion_bound;

    void SetVelocity(); 
};