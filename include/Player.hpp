#pragma once
#include <Character.hpp>

class Player : public Character
{
private:
    
public:
    Player(float dt, sf::Vector2u screen_size);
    ~Player();
    void Reset();

protected:
    
};