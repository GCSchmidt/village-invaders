#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>

class Entity
{
private:

public:
    Entity(float dt, sf::Vector2u screen_size);
    ~Entity();
    uint8_t GetHealthPoints() const;
    sf::Vector2f GetPosition() const;
    bool CheckIfDead() const;
    void SetVelocity(sf::Vector2f velocity); 
    void UpdateVelocity(sf::Vector2f change); 
    void UpdateLocation();
    void Hit();

protected:
    float m_dt;
    uint8_t m_health_points;  // if reduced to zero it dies
    sf::Vector2f m_position;  // pixel location
    sf::Vector2f m_velocity;  // change in location per frame
};