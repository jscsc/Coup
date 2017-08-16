#pragma once
#include <SFML/Graphics.hpp>
#include <string>

// Class representing a menu button
class MenuButton
{

public:

	// Rectangle used to determine if the button is clicked on
	sf::RectangleShape rect;

	// The acutal text of the button (what it displays)
	sf::Text text;

	// Constructors / Destructors
	MenuButton(float x, float y, sf::Font &gameFont, const std::string &message);
	~MenuButton();

	// Renders this button to the given window
	virtual void render(sf::RenderWindow &window);
};

