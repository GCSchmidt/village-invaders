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
    void UpdateVelocity(sf::Vector2f change); 
    void UpdateLocation();
    void Hit();

protected:
    float m_dt;
    uint8_t m_health_points;    // if reduced to zero it dies
    sf::Vector2f m_position;    // center of entity
    float m_speed;              // size of velocity 
    sf::Vector2f m_velocity;    // change in location per frame
    sf::Vector2f m_shape_vector;
    sf::Vector2u m_screen_size;
    sf::Vector2f m_lower_postion_bound;
    sf::Vector2f m_upper_postion_bound;

};