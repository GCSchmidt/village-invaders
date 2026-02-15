#include <Game.hpp>
#include <iostream>

Game::Game()
: m_window(sf::VideoMode(m_window_size), "Village Invaders")
, m_screen(m_window) 
, m_player(Player(m_dt, m_window_size))
{
    m_window.setFramerateLimit(60);
}

Game::~Game()
{
}

void Game::GameLoop()
{   
    while ( m_window.isOpen() && (!m_quit_flag))
	{   
        while (const std::optional event = m_window.pollEvent())
        {

            if ( event->is<sf::Event::Closed>() )
			{
				m_window.close();
			}
            DetectInput();
        }

        HandleState();
        Display();
        
    }
    m_window.close();
}

void Game::PlayLoop()
{
    CheckIfLost();
    HandlePlayerInput();
    UpdateSpriteLocations();
    DetectHits();
    RemoveBullets();
    RemoveDeadEnemies();
}

bool Game::DetectCollision(sf::FloatRect bounding_box_1, sf::FloatRect bounding_box_2)
{
    if (const std::optional intersection = bounding_box_1.findIntersection(bounding_box_2))
    {
        return true;
    }
    return false;
}

void Game::DetectHits()
{
    for (Bullet& bullet : m_bullets)
    {
        sf::FloatRect bullet_box = bullet.GetBoundingBox();
        for (Enemy& enemy : m_enemies)
        {
            sf::FloatRect enemy_box = enemy.GetBoundingBox();
            bool collision = DetectCollision(bullet_box, enemy_box);
            if (collision)
            {
                enemy.Hit(bullet.GetDamage());
                bullet.Hit();
            }
        }  
    } 
}

void Game::DetectInput()
{
    m_detected_keys.esc = false;
    m_detected_keys.enter = false;
    m_detected_keys.p = false;
    m_detected_keys.a = false;
    m_detected_keys.d = false;

    m_detected_keys.esc = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape);
    m_detected_keys.enter = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter);
    m_detected_keys.p = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P);  
    m_detected_keys.space = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space); 
    m_detected_keys.a = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A); 
    m_detected_keys.d = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D); 
}

void Game::HandleState()
{
    switch (m_state)
    {
        case GameState::Menu:
            if (m_detected_keys.esc)
            {
                // m_state = GameState::Exit;
            }
            else if (m_detected_keys.enter)
            {
                m_state = GameState::Playing;
                m_clock.restart();
                SetupGame();
            }
            break;

        case GameState::Playing:
            if (m_detected_keys.p)
            {
                m_state = GameState::Paused;
                m_clock.stop();
            }
            else
            {
                PlayLoop();
            }
            break;

        case GameState::Paused:
            if (m_detected_keys.esc)
            {
                m_state = GameState::Menu;
                m_clock.stop();
            }
            else if (m_detected_keys.enter)
            {
                m_state = GameState::Playing;
                m_clock.start();
            }
            break;
        
        case GameState::Lost:
            if (m_detected_keys.esc)
            {
                m_clock.stop();
                m_state = GameState::Menu;
            }

            break;
        case GameState::Exit:
            break;
    }
}

void Game::HandlePlayerMovement()
{
    float velocity_x = 0;
    float speed = m_player.GetSpeed();

    if (m_detected_keys.a)
    {
       velocity_x -= speed;
    }

    if (m_detected_keys.d)
    {
        velocity_x += speed; 
    }

    sf::Vector2f velocity = sf::Vector2f (velocity_x, 0);

    m_player.SetVelocity(velocity);
}

void Game::HanldePlayerShooting()
{
    static int32_t last_shot_time = 0;
    if (m_detected_keys.space)
    {
        int32_t current_shot_time = m_clock.getElapsedTime().asMilliseconds();
        bool new_shot = m_player.UpdateLastShotTime(current_shot_time);
        if (new_shot)
        {
            sf::Vector2f forward_vector = m_player.GetForwardVector();
            sf::Vector2f position = m_player.GetNewBulletPosition();
            Bullet player_bullet = Bullet(m_dt,
                position, 
                forward_vector,
                BulletSource::Palyer,
                m_window_size
            );
            m_bullets.push_back(player_bullet);
            last_shot_time = current_shot_time; 
        }
    }
}

void Game::HandlePlayerInput()
{  
    HandlePlayerMovement();
    HanldePlayerShooting();
}

void Game::Display()
{   
    m_window.clear();
    switch (m_state)
    {
        case GameState::Menu:
            m_screen.DisplayMenu();
            break;

        case GameState::Playing:
            m_play_time = m_clock.getElapsedTime().asSeconds();
            
            m_screen.DisplayGame(m_play_time);
            m_screen.DisplayLine(m_lose_line_position_y);
            m_screen.DisplayPlayer(m_player);

            DisplayBullets();
            DisplayEnemies();

            break;

        case GameState::Paused:
            m_screen.DisplayPause();
            break;
        
        case GameState::Lost:
            m_screen.DisplayLost();
            break;

        case GameState::Exit:
            m_quit_flag = true;
            break;
    }
    m_window.display();
}

void Game::DisplayBullets()
{
    for (Bullet& bullet : m_bullets)
    {
        m_screen.DisplayBullet(bullet);
    }   
}

void Game::DisplayEnemies()
{
    for (Enemy& enemy : m_enemies)
    {
        m_screen.DisplayEnemy(enemy);
    }   
}

void Game::UpdateSpriteLocations()
{
    // player
    m_player.UpdatePosition();
    
    // bullets
    for (Bullet& bullet : m_bullets)
    {
        bullet.UpdatePosition();
    } 

    // enemies 
    for (Enemy& enemy : m_enemies)
    {
        enemy.UpdatePosition();
    }   
}

void Game::RemoveBullets()
{
    // remove out of bounds bullets
    m_bullets.erase(
        std::remove_if(m_bullets.begin(), m_bullets.end(),
            [](const Bullet& bullet)
            {
                bool condition = (bullet.GetOutOfBounds() || bullet.GetCollided());
                return condition;
            }),
        m_bullets.end()
    );
}

void Game::RemoveDeadEnemies()
{
    m_enemies.erase(
        std::remove_if(m_enemies.begin(), m_enemies.end(),
            [](const Enemy& enemy)
            {
                return enemy.CheckIfDead();
            }),
        m_enemies.end()
    );
}

void Game::CreateEnemies()
{
    uint8_t n_rows = m_n_enemies / m_n_enemies_per_row;
    uint8_t n_cols = m_n_enemies_per_row;
    
    for (uint8_t row = 1 ; row <= n_rows ; row++)
    {
        for (uint8_t col = 1 ; col <= n_cols ; col++)
        {
            //create enemy
            Enemy new_enemy = Enemy(
                m_dt,
                m_window_size, 
                row,
                col,
                m_n_enemies,
                m_n_enemies_per_row
            );
            m_enemies.push_back(new_enemy);
        }
    }
}

void Game::RemoveEnemies()
{
    m_enemies.clear();
}

void Game::SetupGame()
{
    RemoveEnemies();
    m_player.Reset();
    CreateEnemies();
}

void Game::SetQuitFlag()
{
    m_quit_flag = ( m_state == GameState::Exit);
}

bool Game::GetQuitFalg()
{
    return m_quit_flag;
}

void Game::CheckIfLost()
{
    for (Enemy& enemy : m_enemies)
    {
        float position_y = enemy.GetPosition().y;
        
        // enemy has entered the village
        if (position_y >= m_lose_line_position_y)
        {
            m_state = GameState::Lost;
            return;
        }
    }   
}