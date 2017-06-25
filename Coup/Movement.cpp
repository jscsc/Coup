#include "Movement.h"
#include "BoardNode.h"
#include "GamePiece.h"
#include <iostream>

bool Movement::validatePlayerOne(int nodeRow, int nodeColumn, int pieceRow, int pieceColumn)
{
	return (nodeRow == pieceRow - 1) && (nodeColumn == pieceColumn);
}

bool Movement::validatePlayerTwo(int nodeRow, int nodeColumn, int pieceRow, int pieceColumn)
{
	return (nodeRow == pieceRow + 1) && (nodeColumn == pieceColumn);
}

bool Movement::validate(BoardNode &currentNode, GamePiece &currentPiece)
{
	if (currentPiece.getType() == Util::PLAYER_ONE)
		return validatePlayerOne(currentNode.getRow(), currentNode.getColumn(), currentPiece.getRow(), currentPiece.getColumn());
	else
		return validatePlayerTwo(currentNode.getRow(), currentNode.getColumn(), currentPiece.getRow(), currentPiece.getColumn());
}

void Movement::render(sf::RenderWindow &window)
{
	if (selected)
		movementSprite.setTexture(selectedTexture);
	else
		movementSprite.setTexture(baseTexture);
	window.draw(movementSprite);
	//window.draw(rect);
}

void Movement::setPosition(float x, float y)
{

	movementSprite.setPosition(sf::Vector2f(x, y));
	rect.setPosition(sf::Vector2f(x, y));
}

Util::MovementType Movement::getMovementType()
{
	return type;
}

Movement::Movement(sf::Texture & baseTexture, sf::Texture & selectedTexture)
	: Ability(), type(Util::FORWARD), baseTexture(baseTexture), selectedTexture(selectedTexture), rect(sf::Vector2f(64, 64))
{
	setCost(0);
	movementSprite.setTexture(baseTexture);
	rect.setFillColor(sf::Color::Red);

}

Movement::Movement(Util::MovementType type, sf::Texture & baseTexture, sf::Texture & selectedTexture)
: Ability(), type(type), baseTexture(baseTexture), selectedTexture(selectedTexture), rect(sf::Vector2f(64, 64))
{
	setCost(0);
	movementSprite.setTexture(baseTexture);
	rect.setFillColor(sf::Color::Red);
}

//Movement::Movement() : Ability(), type(Util::FORWARD), rect(sf::Vector2f(50, 50))
//{
//	setCost(0);
//	rect.setFillColor(sf::Color::Red);
//	rect.setPosition(sf::Vector2f(300, 700));
//}

//Movement::Movement(Util::MovementType type) : type(type), rect(sf::Vector2f(50, 50))
//{
//	setCost(0);
//	rect.setFillColor(sf::Color::Red);
//	rect.setPosition(sf::Vector2f(300, 700));
//}


Movement::~Movement()
{
}
