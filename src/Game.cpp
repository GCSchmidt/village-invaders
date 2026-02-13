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
                m_state = GameState::Exit;
            }
            else if (m_detected_keys.enter)
            {
                m_state = GameState::Playing;
                m_clock.restart();
            }
            break;

        case GameState::Playing:
            if (m_detected_keys.p)
            {
                m_state = GameState::Paused;
                m_clock.stop();
            }

            
            HandlePlayerInput();
            UpdateEntityLocations();

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

void Game::HanldeShooting()
{
    static int32_t last_shot_time = 0;
    if (m_detected_keys.space)
    {
        int32_t current_shot_time = m_clock.getElapsedTime().asMilliseconds();
        int32_t shot_period = current_shot_time - last_shot_time;
        int32_t min_shot_period = m_player.GetMinShotPeriod();
        if ( shot_period > min_shot_period)
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
    HanldeShooting();
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
            m_screen.DisplayEntity(m_player);
            // display bullets
            
            for (Bullet& bullet : m_bullets)
            {
                m_screen.DisplayBullet(bullet);
            }   

            // display enemies
            break;

        case GameState::Paused:
            m_screen.DisplayPause();
            break;

        case GameState::Exit:
            m_quit_flag = true;
            break;
    }
    m_window.display();
}

void Game::UpdateEntityLocations()
{
    // player
    m_player.UpdatePosition();
    
    // bullets
    for (Bullet& bullet : m_bullets)
    {
        bullet.UpdatePosition();
    } 
    
    // enemies 
    // for enemy do ...
}

void Game::RemoveBullets()
{
    // remove out of bounds bullets
    m_bullets.erase(
        std::remove_if(m_bullets.begin(), m_bullets.end(),
            [](const Bullet& bullet)
            {
                return bullet.GetOutOfBounds();
            }),
        m_bullets.end()
    );
}

void Game::SetQuitFlag()
{
    m_quit_flag = ( m_state == GameState::Exit);
}

bool Game::GetQuitFalg()
{
    return m_quit_flag;
}
