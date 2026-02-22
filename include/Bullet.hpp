#pragma once
#include <Entity.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>

enum class BulletSource
{
    Player,
    Enemy
};

class Bullet : public Entity
{
private:

public:
    Bullet(float dt, sf::Vector2f position, sf::Vector2f forward_vector, BulletSource source, sf::Vector2u screen_size);
    ~Bullet();
    uint8_t GetDamage() const;              
    void DetermineOutOfBounds();            
    bool GetOutOfBounds() const;
    bool GetCollided() const;
    void Hit();
    void UpdatePosition();

protected:
    uint8_t m_damage = 1;               // damage dealt on hit
    bool m_out_of_bounds = false;       // check if bullet is of screen
    bool m_collided = false;            // check if bullett has hot anythings and should be destroyed
    BulletSource m_source;              // what shot the bullet / should maybe be datatype
};