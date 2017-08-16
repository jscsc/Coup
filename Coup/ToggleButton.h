#pragma once
#include "MenuButton.h"
#include <string>

// Class representing a togglable button
class ToggleButton : public MenuButton
{
	// Determines if this button is on or off (toggled or not)
	bool toggled = false;

public:

	// Constructor / Destructors
	ToggleButton(float x, float y, sf::Font &gameFont, const std::string &message);
	~ToggleButton();

	// Getters and Setters
	bool isToggled();
	void setToggled(bool toggled);

	// Renders this button to the given window
	void render(sf::RenderWindow &window) override;
};

