#include <Game.hpp>

Game::Game()
{
}

Game::~Game()
{
}

void Game::GameLoop()
{   
    while ( m_screen.GetWindow().isOpen() && (!m_quit_flag))
	{   
        while (const std::optional event = m_screen.GetWindow().pollEvent())
        {
            if ( event->is<sf::Event::Closed>() )
			{
				m_screen.GetWindow().close();
			}
            // Reset one-frame key flags if needed
            m_detected_keys.esc = false;
            m_detected_keys.enter = false;
            m_detected_keys.p = false;
            DetectInput();
            HandleState();
            // limit frame rate
            // sf::sleep(sf::milliseconds(100));
            Display();
        }
    }
    m_screen.GetWindow().close();
}

void Game::DetectInput()
{
    m_detected_keys.esc = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape);
    m_detected_keys.enter = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter);
    m_detected_keys.p = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P);  
    // m_detected_keys.space = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space); 
    // m_detected_keys.a = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A); 
    // m_detected_keys.d = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D); 
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

void Game::Display()
{
    switch (m_state)
    {
        case GameState::Menu:
            m_screen.DisplayMenu();
            break;

        case GameState::Playing:
            m_screen.DisplayGame();
            break;

        case GameState::Paused:
            m_screen.DisplayPause();
            break;

        case GameState::Exit:
            m_quit_flag = true;
            break;
    }
}

void Game::SetQuitFlag()
{
    m_quit_flag = ( m_state == GameState::Exit);
}

bool Game::GetQuitFalg()
{
    return m_quit_flag;
}
