#include "GameData.h"
#include "BoardNode.h"



GameData::GameData() : currentGameState(Util::ABILITY_SETUP),
currentTurn(Util::NEUTRAL), mouseClicked(true)
{
	float down = 200.0f;
	float right = 300.0f;
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			nodes.push_back(BoardNode(right, down, i, j, 15.0f));
			right += 100;
		}

		right = 300;
		down += 100;
	}
}


GameData::~GameData()
{
}
