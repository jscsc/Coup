#include "MenuButton.h"

MenuButton::MenuButton(float x, float y, sf::Font &gameFont, const std::string &message)
{
	rect.setSize(sf::Vector2f(50, 50));
	rect.setPosition(sf::Vector2f(x, y));
	rect.setFillColor(sf::Color::Red);

	text.setFont(gameFont);
	text.setString(message);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Black);
	text.setPosition(sf::Vector2f(x, y));
}

MenuButton::~MenuButton()
{
}

void MenuButton::render(sf::RenderWindow & window)
{
	window.draw(text);
}
