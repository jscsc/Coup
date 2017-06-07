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
	if(selected)
		rect.setFillColor(sf::Color::Green);
	else
		rect.setFillColor(sf::Color::Red);
	window.draw(rect);
}

Movement::Movement() : Ability(), type(Util::FORWARD), rect(sf::Vector2f(50, 50))
{
	setCost(0);
	rect.setFillColor(sf::Color::Red);
	rect.setPosition(sf::Vector2f(300, 700));
}

Movement::Movement(Util::MovementType type) : type(type), rect(sf::Vector2f(50, 50))
{
	setCost(0);
	rect.setFillColor(sf::Color::Red);
	rect.setPosition(sf::Vector2f(300, 700));
}


Movement::~Movement()
{
}
