#pragma once
#include <Entity.hpp>

class Enemy : public Entity
{
private:
    sf::Vector2f CalculateInitialPostion(uint8_t row, uint8_t col);
    sf::Vector2f m_initial_position;
    void SetOffset(uint8_t n_enemies_per_row);
    void SetMaxXDisplacement();
    void SwitchDirection();
    float m_max_x_displacement;         // max displacement in x diretion 
    sf::Vector2f m_offset;              //gap between centers of enemies 

public:
    Enemy(
        float dt, 
        sf::Vector2u screen_size, 
        uint8_t row, 
        uint8_t col,
        uint8_t n_enemies,
        uint8_t n_enemies_per_row
    );
    ~Enemy();
    void UpdatePosition();

protected:
    void SetPositionBounds();
    
};