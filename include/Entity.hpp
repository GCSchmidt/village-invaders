#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>

class Entity
{
private:

public:
    Entity(float dt, sf::Vector2u screen_size);
    ~Entity();
    void SetVelocity(sf::Vector2f velocity); 
    uint8_t GetHealthPoints() const;
    sf::Vector2f GetTopLeftCorner() const;
    sf::Vector2f GetPosition() const;
    bool CheckIfDead() const;
    float GetSpeed() const;
    uint8_t GetShapeSize() const;
    sf::Vector2f GetShapeVecor() const;
    int32_t GetMinShotPeriod() const;
    sf::Vector2f GetForwardVector() const; 
    sf::Vector2f Entity::GetNewBulletPosition() const;
    void UpdateVelocity(sf::Vector2f change); 
    void UpdatePosition();
    void Hit();

protected:
    float m_dt;
    uint8_t m_health_points;                // if reduced to zero it dies
    float m_speed;                          // size of velocity
    sf::Vector2f m_position;                // center of entity
    sf::Vector2f m_forward_vector;          // unit vector specifying which way the entity is facing
    int32_t m_min_shot_period;              // min duration between shots in milliseconds
    sf::Vector2f m_velocity;                // change in location per frame
    sf::Vector2f m_shape_vector;            // shape of square (w,h)
    sf::Vector2u m_screen_size;             // size of screen
    sf::Vector2f m_lower_postion_bound;     // minimum postion / out of bounds top left
    sf::Vector2f m_upper_postion_bound;     // max position / out of bounds bottom right
    

};