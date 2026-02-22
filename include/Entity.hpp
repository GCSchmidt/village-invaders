#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>

class Entity
{
private:

public:
    Entity(float dt, sf::Vector2u screen_size);
    ~Entity();

    sf::Vector2f GetVelocity() const;
    void SetVelocity(sf::Vector2f velocity); 

    sf::Vector2f GetPosition() const;
    void SetPostion(sf::Vector2f position);

    float GetSpeed() const;

    sf::Vector2f GetTopLeftCorner() const;
    sf::FloatRect GetBoundingBox() const;
    sf::Vector2f GetShapeVecor() const;
    sf::Vector2f GetForwardVector() const; 

    void UpdateVelocity(sf::Vector2f change);       // change velocity by change
    void UpdatePosition(bool clamp);                // update postion based on velocity and if it should be clamped

protected:
    float m_dt;
    sf::Vector2f m_position;                // center of entity
    sf::Vector2f m_forward_vector;          // unit vector specifying which way the entity is facing
    float m_speed;                          // size of velocity
    sf::Vector2f m_velocity;                // change in location per frame
    sf::Vector2f m_shape_vector;            // shape of square/bounding box (w,h)
    sf::Vector2u m_screen_size;             // size of screen
    sf::Vector2f m_lower_postion_bound;     // minimum postion / out of bounds top left
    sf::Vector2f m_upper_postion_bound;     // max position / out of bounds bottom right
    
    void SetPositionBounds();
};