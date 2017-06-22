#pragma once
#include "MenuButton.h"
class ToggleButton : public MenuButton
{

	bool toggled = false;

public:
	ToggleButton(float x, float y);
	~ToggleButton();
	bool isToggled();
	void setToggled(bool toggled);
	void render(sf::RenderWindow &window) override;
};

