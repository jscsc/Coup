#include "GameData.h"
#include "BoardNode.h"

GameData::GameData() : currentGameState(Util::ABILITY_SETUP),
currentTurn(Util::NEUTRAL), mouseClicked(true), exitReady(false), round(1)
{
	float down = 200.0f;
	float right = 300.0f;
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			nodes.push_back(BoardNode(right, down, i, j, 15.0f));
			right += 106;
		}

		right = 300;
		down += 92;
	}
}

GameData::~GameData()
{
}

void GameData::resetAll()
{
	currentGameState = Util::MAIN_MENU;
	currentTurn = Util::NEUTRAL;
	mouseClicked = false;
	exitReady = false;
	round = 1;
	GameOperation::resetBoard(nodes);
	for (BoardNode &node : nodes)
		node.setAissignment(Util::NEUTRAL);
}

void GameData::resetRound()
{
	currentGameState = Util::ABILITY_SETUP;
	currentTurn = Util::NEUTRAL;
	mouseClicked = false;
	exitReady = false;
	GameOperation::resetBoard(nodes);
	for (BoardNode &node : nodes)
		node.setAissignment(Util::NEUTRAL);
}
