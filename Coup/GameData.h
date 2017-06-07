#pragma once
#include "Util.h"
struct GameData
{

	Util::GameState currentGameState;

	Util::PlayerType currentTurn;

	bool mouseClicked;

	GameData();
	~GameData();
};

