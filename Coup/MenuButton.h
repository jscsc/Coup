#pragma once
#include <SFML/Graphics.hpp>
class MenuButton
{


public:
	sf::RectangleShape rect;

	MenuButton(float x, float y);
	~MenuButton();
	 virtual void render(sf::RenderWindow &window);
};

