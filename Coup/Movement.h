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
	sf::Texture &baseTexture;
	sf::Texture &selectedTexture;

public:
	sf::RectangleShape rect;
	sf::Sprite movementSprite;

	bool validate(BoardNode &currentNode, GamePiece &currentPiece);
	void render(sf::RenderWindow &window);
	void setPosition(float x, float y);
	Util::MovementType getMovementType();
	Movement(sf::Texture &baseTexture, sf::Texture &selectedTexture);
	Movement(Util::MovementType type, sf::Texture &baseTexture, sf::Texture &selectedTexture);
	~Movement();
};

