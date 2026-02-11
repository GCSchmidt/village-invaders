#include <Game.hpp>
#include <iostream>

Game::Game()
: m_window(sf::VideoMode(m_window_size), "Village Invaders")
, m_screen(m_window) 
, m_player(Player(m_dt, m_window_size))
{
    m_window.setFramerateLimit(30);
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
        HandlePlayerInput();
        UpdateEntityLocations();
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
    // m_detected_keys.space = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space); 
    m_detected_keys.a = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A); 
    m_detected_keys.d = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D); 
}

void Game::HandleState()
{
    switch (m_state)
    {
        case GameState::Menu:
            if (m_detected_keys.esc)
                m_state = GameState::Exit;
            else if (m_detected_keys.enter)
                m_state = GameState::Playing;
            break;

        case GameState::Playing:
            if (m_detected_keys.p)
                m_state = GameState::Paused;
            break;

        case GameState::Paused:
            if (m_detected_keys.esc)
                m_state = GameState::Menu;
            else if (m_detected_keys.enter)
                m_state = GameState::Playing;
            break;

        case GameState::Exit:
            break;
    }
}

void Game::HandlePlayerInput()
{  

    float velocity_x = 0;
    
    if (m_detected_keys.a);
    {
       velocity_x -= 25;
       std::cout << "A pressed"; 
    }

    if (m_detected_keys.d)
    {
        velocity_x += 25; 
        std::cout << "D pressed"; 
    }

    sf::Vector2f velocity = sf::Vector2f (velocity_x, 0);

    m_player.SetVelocity(velocity);
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
            m_screen.DisplayGame();
            m_screen.DisplayEntity(m_player);
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
    m_player.UpdateLocation();
    
    // enemies 
    // for enemy do ...
}

void Game::SetQuitFlag()
{
    m_quit_flag = ( m_state == GameState::Exit);
}

bool Game::GetQuitFalg()
{
    return m_quit_flag;
}
