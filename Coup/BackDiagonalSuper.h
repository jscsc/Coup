#pragma once
#include "Movement.h"

// Represents the Back Diagonal Super movement ability
class BackDiagonalSuper : public Movement
{

	// Function to validate if the node position passed in meets the requirement for this movment,
	// given the location of the GamePiece passed in. Values are relative to player one starting location
	bool validatePlayerOne(int nodeRow, int nodeColumn, int pieceRow, int pieceColumn) override;

	// Function to validate if the node position passed in meets the requirement for this movment,
	// given the location of the GamePiece passed in. Values are relative to player two starting location
	bool validatePlayerTwo(int nodeRow, int nodeColumn, int pieceRow, int pieceColumn) override;

public:

	// Constructor / Destructor
	BackDiagonalSuper(sf::Texture &baseTexture, sf::Texture &selectedTexture);
	~BackDiagonalSuper();
};

