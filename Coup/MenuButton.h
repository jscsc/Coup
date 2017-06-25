#pragma once
#include <SFML/Graphics.hpp>
#include <string>
class MenuButton
{


public:
	sf::RectangleShape rect;
	sf::Text text;

	MenuButton(float x, float y, sf::Font &gameFont, const std::string &message);
	~MenuButton();
	 virtual void render(sf::RenderWindow &window);
};

