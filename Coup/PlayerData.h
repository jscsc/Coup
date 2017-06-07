#pragma once

#include "Util.h"
#include <vector>
class Movement;
class GamePiece;
struct PlayerData
{

	// The type of player this manager is for
	Util::PlayerType type;

	// Points remaining for this plater
	int points;

	// True if any piece beloning to this player is moving, false otherwise
	bool pieceMoving;

	// The current game piece selected by this player
	GamePiece* currentGamePiece;

	// The current Movement selected by this player
	Movement* currentMovement;

	// List of all this player's game pieces currently on the board
	std::vector< GamePiece > pieces;

	std::vector< Movement* > movements;

	Movement defaultMovement;

	PlayerData();
	PlayerData(Util::PlayerType type);
	~PlayerData();
	void resetCurrentMovement();

};

