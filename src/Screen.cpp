#include <Screen.hpp>

Screen::Screen()
{
}

Screen::~Screen()
{
}

void Screen::SetDisplayText(std::string new_text)
{
    m_display_text = new_text;
}

sf::RenderWindow& Screen::GetWindow()
{
    return m_window;
}

void Screen::WriteText()
{
    sf::Text text(m_font, m_display_text);
	text.setCharacterSize(30);
	text.setStyle(sf::Text::Bold);
	text.setFillColor(sf::Color::White);
	sf::Vector2f text_size = text.getLocalBounds().size;
	sf::Vector2f new_text_position = (sf::Vector2f(m_window_size) / 2.f) - (text_size / 2.f); 
	text.setPosition(new_text_position);
    m_window.draw(text);
}

void Screen::DisplayMenu()
{
    SetDisplayText("Press [ENTER] to Start or [ESC] to Quit");
    m_window.clear();
	WriteText();
	m_window.display();
}

void Screen::DisplayPause()
{
    SetDisplayText("Press [ENTER] to Resume or [ESC] for Menu");
    m_window.clear();
	WriteText();
	m_window.display();
}

void Screen::DisplayGame()
{
    SetDisplayText("You are Playing");
    m_window.clear();
	WriteText();
	m_window.display();
}