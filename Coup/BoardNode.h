#pragma once
#include <SFML/Graphics.hpp>
#include "BoardObject.h"
#include "Util.h"
class BoardNode : public BoardObject
{

	bool valid = false;
	Util::PlayerType assignment = Util::NEUTRAL;


public:

	sf::CircleShape body;

	BoardNode();
	BoardNode(float x, float y, int row, int column, float size);
	~BoardNode();
	void setValid(bool valid);
	bool isValid();
	Util::PlayerType getAssignment();
	void setAissignment(Util::PlayerType assignment);
	void render(sf::RenderWindow &window) override;
};

