#pragma once
#include <SFML/Graphics.hpp>
#include "BoardObject.h"
class BoardNode : public BoardObject
{

	bool valid = false;
	bool occupied  = false;


public:

	sf::CircleShape body;

	BoardNode();
	BoardNode(float x, float y, int row, int column, float size);
	~BoardNode();
	void setValid(bool valid);
	bool isValid();
	void setOccupied(bool occupied);
	bool isOccupied();
	void render(sf::RenderWindow &window) override;
};

