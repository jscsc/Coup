#include "MenuButton.h"



MenuButton::MenuButton(float x, float y)
{
	rect.setSize(sf::Vector2f(50, 50));
	rect.setPosition(sf::Vector2f(x, y));
	rect.setFillColor(sf::Color::Red);
}


MenuButton::~MenuButton()
{
}

void MenuButton::render(sf::RenderWindow & window)
{
	window.draw(rect);
}
