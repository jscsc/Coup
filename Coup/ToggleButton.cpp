#include "ToggleButton.h"



ToggleButton::ToggleButton(float x, float y) : MenuButton(x, y), toggled(false)
{
}


ToggleButton::~ToggleButton()
{
}

bool ToggleButton::isToggled()
{
	return toggled;
}

void ToggleButton::setToggled(bool toggled)
{
	this->toggled = toggled;
}

void ToggleButton::render(sf::RenderWindow & window)
{
	if (toggled)
		rect.setFillColor(sf::Color::Green);
	else
		rect.setFillColor(sf::Color::Red);

	window.draw(rect);
}
