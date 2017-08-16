#pragma once
#include "Util.h"
#include <vector>
#include "Movement.h"
class GamePiece;
struct Textures;

// Struct holding Data relevant to a player
struct PlayerData
{

	// The type of player this struct is for
	Util::PlayerType type;

	// Points remaining for this plater
	int points;

	// The overall score for this player
	int score;

	// Pieces that have been placed on the board
	int assignedPieces;

	// True if any piece beloning to this player is moving, false otherwise
	bool pieceMoving;

	// Is the player done with their current turn?
	bool ready;

	// Reference to all the textures in the game
	Textures &textures;

	// The current game piece selected by this player
	GamePiece* currentGamePiece;

	// The current Movement selected by this player
	Movement* currentMovement;

	// List of all this player's game pieces currently on the board
	std::vector< GamePiece* > pieces;

	// List of all this player's current movements
	std::vector< Movement* > movements;

	// Default movement for this player
	Movement defaultMovement;

	// Constructors / Destructor
	PlayerData(Util::PlayerType type, Textures &textures);
	~PlayerData();

	// Resets the current movement to the default movement
	void resetCurrentMovement();

	// Sets up the GamePieces of this player
	void setupGamePieces();

	// Resets all data for this player
	void resetAll();

	// Resets data relevant to a round for this player
	void resetRound();

	// Resets the GamePieces for this player
	void resetGamePieces();
};

