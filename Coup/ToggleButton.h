#pragma once
#include "MenuButton.h"
#include <string>
class ToggleButton : public MenuButton
{

	bool toggled = false;

public:
	ToggleButton(float x, float y, sf::Font &gameFont, const std::string &message);
	~ToggleButton();
	bool isToggled();
	void setToggled(bool toggled);
	void render(sf::RenderWindow &window) override;
};

