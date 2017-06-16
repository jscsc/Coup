#include "GamePiece.h"
#include "Arrive.h"
#include <iostream>

GamePiece::GamePiece(Util::PlayerType owner, float x, float y, int row, int column, float size)
	: BoardObject(row, column), MAX_ACCELERATION(2.0f), MAX_SPEED(0.5f), TARGET_RADIUS(0.5f),
	SLOW_RADIUS(100.0f), window(window), owner(owner), target(), body(size), selected(false), active(true), onBoard(false),
	arrive(kinematic, target, MAX_ACCELERATION, MAX_SPEED, TARGET_RADIUS, SLOW_RADIUS)
{
	kinematic.position.x = x;
	kinematic.position.y = y;
	body.setOrigin(body.getRadius(), body.getRadius());
	body.setPosition(kinematic.position);
	setMovementTargetPosition(x, y);
	body.setFillColor(sf::Color::White);
}

GamePiece::~GamePiece()
{
}

void GamePiece::render(sf::RenderWindow &window)
{
	body.setPosition(kinematic.position);
	window.draw(body);
}

void GamePiece::move()
{
	SteeringOutput output = arrive.getSteering();
	kinematic.update(output);
}

void GamePiece::setMovementTargetPosition(float x, float y)
{
	arrive.target.position.x = x;
	arrive.target.position.y = y;
}

Util::PlayerType GamePiece::getType()
{
	return owner;
}

void GamePiece::setArriveTarget(float x, float y)
{
	arrive.target.position.x = x;
	arrive.target.position.y = y;
}

void GamePiece::setActive(bool active)
{
	this->active = active;
}

void GamePiece::setSelected(bool selected)
{
	if (selected)
		body.setFillColor(sf::Color::Yellow);
	else
		body.setFillColor(sf::Color::White);
	this->selected = selected;
}

bool GamePiece::isActive()
{
	return active;
}

bool GamePiece::isSelected()
{
	return selected;
}

bool GamePiece::isOnBoard()
{
	return onBoard;
}

bool GamePiece::setOnBoard(bool onBoard)
{
	return this->onBoard = onBoard;
}

