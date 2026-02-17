#include <Screen.hpp>

Screen::Screen(sf::RenderWindow& window)
: m_window(window)
{
}

Screen::~Screen()
{
}

void Screen::SetCenterText(std::string new_text)
{
    m_center_text = new_text;
}

void Screen::SetHudText(std::string new_text)
{
    m_hud_text = new_text;
}

void Screen::WriteCenterText()
{
    sf::Vector2u window_size = m_window.getSize();
	sf::Text center_text(m_font, m_center_text);
	center_text.setCharacterSize(30);
	center_text.setStyle(sf::Text::Bold);
	center_text.setFillColor(sf::Color::White);
	sf::Vector2f center_text_size = center_text.getLocalBounds().size;
	sf::Vector2f center_text_position = (sf::Vector2f(window_size) / 2.f) - (center_text_size / 2.f); 
	center_text.setPosition(center_text_position);
    m_window.draw(center_text);
}

void Screen::WriteHudText()
{
	sf::Vector2u window_size = m_window.getSize();
	sf::Text hud_text(m_font, m_hud_text);
	hud_text.setCharacterSize(18);
	hud_text.setStyle(sf::Text::Bold);
	hud_text.setFillColor(sf::Color::White);
	sf::Vector2f hud_text_size = hud_text.getLocalBounds().size;
	sf::Vector2f hud_text_position;
	hud_text_position.x = window_size.x - hud_text_size.x * 1.5 ;
	hud_text_position.y = hud_text_size.y / 2.f;
	hud_text.setPosition(hud_text_position);
    m_window.draw(hud_text);
}

void Screen::DisplayMenu()
{
    SetCenterText("Press [ENTER] to Start");
	WriteCenterText();
}

void Screen::DisplayPause()
{
    SetCenterText("Game is Paused\nPress [ENTER] to Resume\nor [ESC] for Menu");
	WriteCenterText();
}

void Screen::DisplayLost()
{
	SetCenterText("You Failed to Save the Village\nPress [ESC] for Menu");
	WriteCenterText();
}

void Screen::DisplayVictory()
{
	SetCenterText("You Saved the Village\nPress [ESC] for Menu");
	WriteCenterText();
}

void Screen::DisplayGame(float play_time)
{
	int rounded_play_time = int(play_time);
	std::string display_text = "Time: " + std::to_string(rounded_play_time);
	SetHudText(display_text);
	WriteHudText();
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
