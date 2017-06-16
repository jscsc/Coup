#pragma once
#include <SFML/Graphics.hpp>
#include "BoardObject.h"
#include "Util.h"
#include "Arrive.h"

//class Arrive;
class GamePiece : public BoardObject
{

	// Constants for the arrive algorithm
	const float MAX_ACCELERATION;
	const float MAX_SPEED;
	const float TARGET_RADIUS;
	const float SLOW_RADIUS;

	sf::RenderWindow &window;
	Util::PlayerType owner;
	Arrive arrive;
	Kinematic target;
	bool active = false;
	bool selected = false;
	bool onBoard = false;


public:
	sf::CircleShape body;
	GamePiece(Util::PlayerType owner, float x, float y, int row, int column, float size);
	~GamePiece();
	void render(sf::RenderWindow &window) override;
	void move();
	void setMovementTargetPosition(float x, float y);
	Util::PlayerType getType();
	void setArriveTarget(float x, float y);
	void setActive(bool active);
	void setSelected(bool selected);
	bool isActive();
	bool isSelected();
	bool isOnBoard();
	bool setOnBoard(bool onBoard);

};


