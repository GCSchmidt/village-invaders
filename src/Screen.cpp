#include <Screen.hpp>

Screen::Screen(sf::RenderWindow& window)
: m_window(window)
{
}

Screen::~Screen()
{
}

void Screen::SetDisplayText(std::string new_text)
{
    m_display_text = new_text;
}

void Screen::WriteText()
{
    sf::Text text(m_font, m_display_text);
	text.setCharacterSize(30);
	text.setStyle(sf::Text::Bold);
	text.setFillColor(sf::Color::White);
	sf::Vector2f text_size = text.getLocalBounds().size;
	sf::Vector2u window_size = m_window.getSize();
	sf::Vector2f new_text_position = (sf::Vector2f(window_size) / 2.f) - (text_size / 2.f); 
	text.setPosition(new_text_position);
    m_window.draw(text);
}

void Screen::DisplayMenu()
{
    SetDisplayText("Press [ENTER] to Start or [ESC] to Quit");
	WriteText();
}

void Screen::DisplayPause()
{
    SetDisplayText("Press [ENTER] to Resume or [ESC] for Menu");
	WriteText();
}

void Screen::DisplayGame()
{
	SetDisplayText("You are playing");
	WriteText();
}

void Screen::DisplayEntity(const Entity& entity)
{
	sf::Vector2f shape_vector = entity.GetShapeVecor();
	sf::RectangleShape shape = sf::RectangleShape( shape_vector );
	shape.setFillColor( sf::Color::Green );
	sf::Vector2f top_left_corner = entity.GetTopLeftCorner();
	shape.setPosition(top_left_corner);
	m_window.draw(shape);
}