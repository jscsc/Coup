#pragma once
#include <SFML/Graphics.hpp>
class MenuButton
{


public:
	sf::RectangleShape rect;

	MenuButton();
	~MenuButton();
	 virtual void render(sf::RenderWindow &window);
};

