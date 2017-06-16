#pragma once
#include "Util.h"
#include <vector>
#include "Movement.h"
class GamePiece;
struct PlayerData
{

	// The type of player this manager is for
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

	// The current game piece selected by this player
	GamePiece* currentGamePiece;

	// The current Movement selected by this player
	Movement* currentMovement;

	// List of all this player's game pieces currently on the board
	std::vector< GamePiece* > pieces;

	std::vector< Movement* > movements;

	Movement defaultMovement;

	PlayerData();
	PlayerData(Util::PlayerType type);
	~PlayerData();
	void resetCurrentMovement();

};

