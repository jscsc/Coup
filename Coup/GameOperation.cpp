#include "GameOperation.h"
#include "Movement.h"
#include "Stay.h"
#include "Back.h"
#include "LeftOrRight.h"
#include "Diagonal.h"
#include "Super.h"
#include "BoardNode.h"
#include "PlayerData.h"
#include "GameData.h"
#include "GamePiece.h"



Util::MovementType GameOperation::combineMovement(Util::MovementType currentType, Util::MovementType additionalType)
{
	return Util::MovementType();
}

Util::MovementType GameOperation::separateMovement(Util::MovementType currentType, Util::MovementType removalType)
{
	return Util::MovementType();
}

void GameOperation::validatePositionSetupBoard(std::vector<BoardNode>& nodes, PlayerData & playerData)
{
	int targetRow;

	if (playerData.type == Util::PLAYER_ONE)
		targetRow = 4;
	else
		targetRow = 0;

	for (BoardNode &node : nodes) {
		if (node.getRow() == targetRow)
			node.setValid(true);
		else
			node.setValid(false);
	}
}

void GameOperation::addMovement(PlayerData &playerData, Util::MovementType type)
{
	switch (type)
	{
		case Util::BACK:
			playerData.movements.push_back(new Back());
			break;
		case Util::STAY:
			playerData.movements.push_back(new Stay());
			break;
		case Util::LEFT_OR_RIGHT:
			playerData.movements.push_back(new LeftOrRight());
			break;
		case Util::DIAGONAL:
			playerData.movements.push_back(new Diagonal());
			break;
		case Util::SUPER:
			playerData.movements.push_back(new Super());
			break;
		default:
			break;
	}


}

void GameOperation::resetBoard(std::vector<BoardNode>& nodes)
{
	for (BoardNode &node : nodes)
		node.setValid(false);
}

void GameOperation::validateBoard(PlayerData & playerData, GameData & gameData)
{
	if (playerData.currentGamePiece == nullptr) {
		resetBoard(gameData.nodes);
		return;
	}

	for (BoardNode &node : gameData.nodes)
		node.setValid(playerData.currentMovement->validate(node, *playerData.currentGamePiece));
}

void GameOperation::executeMovement(PlayerData & playerData, BoardNode & node)
{
	playerData.currentGamePiece->setRow(node.getRow());
	playerData.currentGamePiece->setColumn(node.getColumn());
	playerData.currentGamePiece->setMovementTargetPosition(node.kinematic.position.x, node.kinematic.position.y);
	playerData.points -= playerData.currentMovement->getCost();
	playerData.ready = true;
	node.setAissignment(playerData.type);
}

void GameOperation::unassignNode(int row, int column, GameData & gameData)
{
	for (BoardNode &node : gameData.nodes) {
		if (node.getRow() == row && node.getColumn() == column) {
			node.setAissignment(Util::NEUTRAL);
			break;
		}
	}
}

bool GameOperation::piecesAssigned(PlayerData & playerData)
{
	return playerData.assignedPieces == playerData.pieces.size();
}

GameOperation::GameOperation()
{

}


GameOperation::~GameOperation()
{

}
