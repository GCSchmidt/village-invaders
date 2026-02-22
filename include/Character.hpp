#pragma once
#include <Entity.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>

class Character : public Entity
{
private:

public:
    Character(float dt, sf::Vector2u screen_size);
    ~Character();

    bool UpdateLastShotTime(int32_t current_shot_time);
    uint8_t GetHealthPoints() const;
    bool CheckIfDead() const;
    int32_t GetMinShotPeriod() const;
    sf::Vector2f GetNewBulletPosition() const;
    void Hit(uint8_t damage);

protected:
    uint8_t m_health_points;                // if reduced to zero it dies
    int32_t m_min_shot_period;              // min duration between shots in milliseconds
    int32_t m_last_shot_time = -1;          // time in miliseconds when last shot was taken
};