#pragma once
#include <vector>
#include "Util.h"
class BoardNode;
struct GameData
{

	Util::GameState currentGameState;

	Util::PlayerType currentTurn;

	bool mouseClicked;

	std::vector< BoardNode > nodes;

	GameData();
	~GameData();
};

