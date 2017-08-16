#pragma once
#include <SFML/Graphics.hpp>
#include "Ability.h"
#include "Util.h"
class BoardNode;
class GamePiece;

// Base class for all movements that can be made by the player
class Movement : public Ability
{

	// Function to validate if the node position passed in meets the requirement for this movment,
	// given the location of the GamePiece passed in. Values are relative to player one starting location
	virtual bool validatePlayerOne(int nodeRow, int nodeColumn, int pieceRow, int pieceColumn);

	// Function to validate if the node position passed in meets the requirement for this movment,
	// given the location of the GamePiece passed in. Values are relative to player two starting location
	virtual bool validatePlayerTwo(int nodeRow, int nodeColumn, int pieceRow, int pieceColumn);

protected:

	// Signifies the type of Movement this instance is
	Util::MovementType type;

	// Reference to the texture of this Movement when it is not selected
	sf::Texture &baseTexture;

	// Reference to the texture of this Movement when it is selected
	sf::Texture &selectedTexture;

public:

	// Rectangle object used for click detection
	sf::RectangleShape rect;

	// The Sprite used to show this Movement on the window
	sf::Sprite movementSprite;

	// Determines if the currenet GamePiece can move to the current BoardNode using this Movement
	bool validate(BoardNode &currentNode, GamePiece &currentPiece);

	// Renders this Movement to the window
	void render(sf::RenderWindow &window);

	// Getters and Setters
	void setPosition(float x, float y);
	Util::MovementType getMovementType();

	// Constructors / Destructor
	Movement(sf::Texture &baseTexture, sf::Texture &selectedTexture);
	Movement(Util::MovementType type, sf::Texture &baseTexture, sf::Texture &selectedTexture);
	~Movement();
};

