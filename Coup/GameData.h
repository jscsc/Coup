#pragma once
#include <vector>
#include "Util.h"
#include "GameOperation.h"
class BoardNode;

// Struct to hold overall game data
struct GameData
{
	// Holds the current state of the game
	Util::GameState currentGameState;

	// Holds the current player turn of the game
	Util::PlayerType currentTurn;

	// Determines if the mouse button has been clicked this loop iteration
	bool mouseClicked;

	// Determines if the exit button has been clicked this loop iteration
	bool exitReady;

	// Holds the current round of the game
	int round;

	// Holds the BoardNodes used in the game
	// TODO convert this to a 2D Array
	std::vector< BoardNode > nodes;

	// Constructors / Destructors
	GameData();
	~GameData();

	// Resets the Data in the GameData struct
	void resetAll();

	// Resets the data relevant to a round in the game
	void resetRound();
};

