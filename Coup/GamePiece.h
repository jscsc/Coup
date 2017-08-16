#pragma once
#include <SFML/Graphics.hpp>
#include "BoardObject.h"
#include "Util.h"
#include "Arrive.h"

// Class representing a game piece on the game board
class GamePiece : public BoardObject
{

	// Constants for the arrive algorithm
	const float MAX_ACCELERATION;
	const float MAX_SPEED;
	const float TARGET_RADIUS;
	const float SLOW_RADIUS;

	// The window to redner to
	sf::RenderWindow &window;

	// Determines which player owns this GamePiece
	Util::PlayerType owner;

	// Arrive algorithm for this GamePiece
	Arrive arrive;

	// The target for this GamePiece's arrive algorithm
	Kinematic target;

	// Determines if this GamePiece is active (can be used)
	bool active = false;

	// Determines if this GamePiece is selected (will be used)
	bool selected = false;

	// Determines if this GamePiece
	bool onBoard = false;


public:

	// The body to render for this GamePiece
	sf::CircleShape body;

	// Constructors / Destructors
	GamePiece(Util::PlayerType owner, float x, float y, int row, int column, float size);
	~GamePiece();

	// Renders the GamePiece to the window
	void render(sf::RenderWindow &window) override;

	// Moves the GamePiece using the Arrive Steering Behavior
	void move();

	// Sets the Target Positoin for where this piece should move
	void setMovementTargetPosition(float x, float y);

	// Sets the position of the GamePiece
	void setPosition(float x, float y);

	// Getters and Setters
	Util::PlayerType getType();
	void setArriveTarget(float x, float y);
	void setActive(bool active);
	void setSelected(bool selected);
	bool isActive();
	bool isSelected();
	bool isOnBoard();
	bool setOnBoard(bool onBoard);

private:
	void setColor();

};


