#pragma once
#include <vector>
#include "Util.h"
#include "GameOperation.h"
class BoardNode;
struct GameData
{

	Util::GameState currentGameState;

	Util::PlayerType currentTurn;

	bool mouseClicked;

	bool exitReady;

	int round;

	std::vector< BoardNode > nodes;

	GameData();
	~GameData();
	void resetAll();
	void resetRound();
};

