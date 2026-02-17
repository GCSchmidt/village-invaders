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
    SetDisplayText("Press [ENTER] to Start");
	WriteText();
}

void Screen::DisplayPause()
{
    SetDisplayText("Game is Paused\nPress [ENTER] to Resume\nor [ESC] for Menu");
	WriteText();
}

void Screen::DisplayLost()
{
	SetDisplayText("You Failed to Save the Village\nPress [ESC] for Menu");
	WriteText();
}

void Screen::DisplayVictory()
{
	SetDisplayText("You Saved the Village\nPress [ESC] for Menu");
	WriteText();
}

void Screen::DisplayGame(float play_time)
{
	float rounded_play_time = std::round(play_time);
	std::string display_text = "Time: " + std::to_string(rounded_play_time) + "s";
	SetDisplayText(display_text);
	WriteText();
}

void Screen::DisplayLine(float m_lose_line_position_y)
{
	sf::Vector2f shape_vector;
	sf::Vector2u window_size = m_window.getSize();
	shape_vector.x = window_size.x;
	shape_vector.y = 10;
	sf::RectangleShape shape = sf::RectangleShape( shape_vector );
	shape.setFillColor( sf::Color::White );
	sf::Vector2f top_left_corner;
	top_left_corner.x = 0;
	top_left_corner.y = m_lose_line_position_y;
	shape.setPosition(top_left_corner);
	m_window.draw(shape);
}

void Screen::DisplayEnemy(const Entity& entity)
{
	// sf::Vector2f shape_vector = entity.GetShapeVecor();
	// sf::RectangleShape shape = sf::RectangleShape( shape_vector );
	// shape.setFillColor( sf::Color::Red );
	// sf::Vector2f top_left_corner = entity.GetTopLeftCorner();
	// shape.setPosition(top_left_corner);
	// m_window.draw(shape);
	static sf::Vector2u texture_size = m_enemy_texture.getSize();
	static sf::Vector2f shape_vector = entity.GetShapeVecor();
	static sf::Vector2f scale;
	scale.x = shape_vector.x / texture_size.x;
	scale.y = shape_vector.y / texture_size.y;
	sf::Vector2f top_left_corner = entity.GetTopLeftCorner();
	m_enemy_sprite.setPosition(top_left_corner);
	m_enemy_sprite.setScale(scale);
	m_window.draw(m_enemy_sprite);
}

void Screen::DisplayPlayer(const Entity& entity)
{
	static sf::Vector2u texture_size = m_player_texture.getSize();
	static sf::Vector2f shape_vector = entity.GetShapeVecor();
	static sf::Vector2f scale;
	scale.x = shape_vector.x / texture_size.x;
	scale.y = shape_vector.y / texture_size.y;
	sf::Vector2f top_left_corner = entity.GetTopLeftCorner();
	m_player_sprite.setPosition(top_left_corner);
	m_player_sprite.setScale(scale);
	m_window.draw(m_player_sprite);
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

void Screen::DisplayBullet(const Bullet &bullet)
{
	static sf::Vector2u texture_size = m_bullet_texture.getSize();
	static sf::Vector2f shape_vector = bullet.GetShapeVecor();
	static sf::Vector2f scale;
	scale.x = shape_vector.x / texture_size.x;
	scale.y = shape_vector.y / texture_size.y;
	sf::Vector2f top_left_corner = bullet.GetTopLeftCorner();
	m_bullet_sprite.setPosition(top_left_corner);
	m_bullet_sprite.setScale(scale);
	m_window.draw(m_bullet_sprite);
}
