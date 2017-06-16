#pragma once
#include "MenuButton.h"
class ToggleButton : public MenuButton
{

	bool toggled;

public:
	ToggleButton();
	~ToggleButton();
	bool isToggled();
	void setToggled(bool toggled);
	void render(sf::RenderWindow &window) override;
};

