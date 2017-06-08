#pragma once
#include <SFML/Graphics.hpp>
#include "Ability.h"
#include "Util.h"
class BoardNode;
class GamePiece;
class Movement : public Ability
{

	virtual bool validatePlayerOne(int nodeRow, int nodeColumn, int pieceRow, int pieceColumn);
	virtual bool validatePlayerTwo(int nodeRow, int nodeColumn, int pieceRow, int pieceColumn);

protected:

	Util::MovementType type; // <-- protected data member

public:
	sf::RectangleShape rect;

	bool validate(BoardNode &currentNode, GamePiece &currentPiece);
	void render(sf::RenderWindow &window);
	void setPosition(float x, float y);
	Movement();
	Movement(Util::MovementType type);
	~Movement();
};

