#include "AIManager.h"
#include "PlayerData.h"
#include "GameData.h"
#include "UIData.h"
#include <random>
#include "GamePiece.h"
#include "BoardNode.h"
#include "GameOperation.h"
#include <iostream>



AIManager::AIManager(PlayerData & AIData, GameData & gameData, UIData &UI) : AIData(AIData), gameData(gameData), UI(UI)
{

}

AIManager::~AIManager()
{

}

void AIManager::AIPlayerLogic()
{
	switch (gameData.currentGameState)
	{

		case Util::ABILITY_SETUP:
			handelAIAbilitySetup();
			break;
		case Util::POSITION_SETUP:
			handelAIPositionSetup();
			break;
		case Util::GAMEPLAY:
			handelAIGameplay();
			break;
		default:
			break;

	}
	
}

void AIManager::handelAIAbilitySetup()
{
	if (AIData.ready)
		return;

	while (AIData.points < 4) {
		std::random_device randomDevice; // Obtain a random number from hardware
		std::mt19937 engine(randomDevice()); // seed the generator
		std::uniform_int_distribution<> distribution(0, UI.movementSelection.size() - 1); // define the range
		int randomInt = distribution(engine);

		if (UI.movementSelection[randomInt]->getCost() + AIData.points <= 4) {
			GameOperation::addMovement(AIData, UI.movementSelection[randomInt]->getMovementType());
			AIData.points += UI.movementSelection[randomInt]->getCost();
		}

	}
	GameOperation::addMovement(AIData, Util::FORWARD);
	AIData.ready = true;
}

void AIManager::handelAIPositionSetup()
{

	if (gameData.currentTurn != AIData.type || AIData.ready)
		return;

	// If we have already assigned all our pieces, no reason to be here
	if (AIData.assignedPieces == AIData.pieces.size()) {
		GameOperation::resetBoard(gameData.nodes);
		return;
	}

	// Show available spaces to move
	GameOperation::validatePositionSetupBoard(gameData.nodes, AIData);

	std::random_device randomDevice; // Obtain a random number from hardware
	std::mt19937 engine(randomDevice()); // seed the generator
	std::uniform_int_distribution<> distribution(0, 4); // define the range for rows

	for (GamePiece *piece : AIData.pieces)
		if (!piece->isOnBoard())
			AIData.currentGamePiece = piece;

	// TODO fix this logic

	while (!AIData.ready) {
		int randomColumn = distribution(engine);
		for (BoardNode &node : gameData.nodes) {
			if (node.isValid() && node.getAssignment() != AIData.type && node.getColumn() == randomColumn) {
				GameOperation::executeMovement(AIData, node);
				AIData.currentGamePiece->setOnBoard(true);
				AIData.assignedPieces++;
				break;
			}
		}
	}
	GameOperation::resetBoard(gameData.nodes);
}

void AIManager::handelAIGameplay()
{
	if (gameData.currentTurn != AIData.type || AIData.ready)
		return;

	if (AIData.pieces.size() == 0)
		return;

	std::random_device randomDevice; // Obtain a random number from hardware
	std::mt19937 engine(randomDevice()); // seed the generator
	std::uniform_int_distribution<> distribution(0, AIData.pieces.size() - 1); // define the range

	// TODO Fix this logic, it selects pieces that are alrady dead
	int randomInt = distribution(engine);
	AIData.currentGamePiece = AIData.pieces[randomInt];

	// This might of broke something, single it out
	if (!AIData.currentGamePiece->isActive())
		return;

	determineMove();
}

void AIManager::determineMove()
{
	for (Movement * movement : AIData.movements) {
		if (movement->isActive()) {
			AIData.currentMovement = movement;
			tryMove();
		}
		if (AIData.ready)
			break;
	}
}

void AIManager::tryMove()
{
	switch (AIData.currentMovement->getMovementType())
	{
		case Util::STAY:
			handelStay();
			break;
		case Util::BACK:
			handelBack();
			break;
		case Util::LEFT_OR_RIGHT:
			handelLeftOrRight();
			break;
		case Util::DIAGONAL:
			handelDiagonal();
			break;
		case Util::SUPER:
			handelSuper();
			break;
		default:
			handelDefault();
			break;

	}
}

void AIManager::handelBack()
{
	if (inDanger()) {
		GameOperation::validateBoard(AIData, gameData);
		for (BoardNode &node : gameData.nodes) {
			if (node.isValid() && node.getAssignment() != AIData.type) {
				// Do the move
				std::cout << "Moving with Back" << std::endl;
				// Did I forget to unassignNode here?
				GameOperation::unassignNode(AIData.currentGamePiece->getRow(), AIData.currentGamePiece->getColumn(), gameData);
				GameOperation::executeMovement(AIData, node);
				break;
			}
		}
	}
}

void AIManager::handelStay()
{
	if (inDanger()) {
		GameOperation::validateBoard(AIData, gameData);
		for (BoardNode &node : gameData.nodes) {
			if (node.isValid()) {
				// Do the move
				std::cout << "Moving with Stay" << std::endl;
				GameOperation::unassignNode(AIData.currentGamePiece->getRow(), AIData.currentGamePiece->getColumn(), gameData);
				GameOperation::executeMovement(AIData, node);
				break;
			}
		}
	}
}

void AIManager::handelLeftOrRight()
{
	GameOperation::validateBoard(AIData, gameData);
	for (BoardNode &node : gameData.nodes) {
		if (node.isValid() && node.getAssignment() == Util::PLAYER_ONE) {
			std::cout << "Moving with LeftOrRIght" << std::endl;
			GameOperation::unassignNode(AIData.currentGamePiece->getRow(), AIData.currentGamePiece->getColumn(), gameData);
			GameOperation::executeMovement(AIData, node);
			break;
		}
	}
}

void AIManager::handelDiagonal()
{
	GameOperation::validateBoard(AIData, gameData);
	for (BoardNode &node : gameData.nodes) {
		if (node.isValid() && node.getAssignment() == Util::PLAYER_ONE) {
			std::cout << "Moving with Diagonal" << std::endl;
			GameOperation::unassignNode(AIData.currentGamePiece->getRow(), AIData.currentGamePiece->getColumn(), gameData);
			GameOperation::executeMovement(AIData, node);
			break;
		}
	}
}

void AIManager::handelSuper()
{
	GameOperation::validateBoard(AIData, gameData);
	for (BoardNode &node : gameData.nodes) {
		if (node.isValid() && node.getAssignment() == Util::PLAYER_ONE) {
			std::cout << "Moving with Super" << std::endl;
			GameOperation::unassignNode(AIData.currentGamePiece->getRow(), AIData.currentGamePiece->getColumn(), gameData);
			GameOperation::executeMovement(AIData, node);
			break;
		}
	}
}

void AIManager::handelDefault()
{
	GameOperation::validateBoard(AIData, gameData);
	for (BoardNode &node : gameData.nodes) {
		if (node.isValid()) {
			std::cout << "Moving with Default" << std::endl;
			GameOperation::unassignNode(AIData.currentGamePiece->getRow(), AIData.currentGamePiece->getColumn(), gameData);
			GameOperation::executeMovement(AIData, node);
			AIData.currentMovement->setActive(true);
			break;
		}
	}
}

bool AIManager::dangerForward()
{
	int forwardRow = AIData.currentGamePiece->getRow() + 2;
	for (BoardNode &node : gameData.nodes) {
		if (node.getRow() == forwardRow && node.getColumn() == AIData.currentGamePiece->getColumn() 
			&& node.getAssignment() == Util::PLAYER_ONE) {
			return true;
		}
	}
	return false;
}


bool AIManager::dangerForwardLeft()
{
	int leftCol = AIData.currentGamePiece->getColumn() - 1;
	int forwardRow = AIData.currentGamePiece->getRow() + 1;
	for (BoardNode &node : gameData.nodes) {
		if (node.getRow() == forwardRow  && node.getColumn() == leftCol
			&& node.getAssignment() == Util::PLAYER_ONE) {
			return true;
		}
	}
	return false;
}

bool AIManager::dangerForwardRight()
{
	int rightCol = AIData.currentGamePiece->getColumn() + 1;
	int forwardRow = AIData.currentGamePiece->getRow() + 1;
	for (BoardNode &node : gameData.nodes) {
		if (node.getRow() == forwardRow  && node.getColumn() == rightCol
			&& node.getAssignment() == Util::PLAYER_ONE) {
			return true;
		}
	}
	return false;
}

bool AIManager::dangerDiagonalLeft()
{
	int leftCol = AIData.currentGamePiece->getColumn() - 1;
	int forwardRow = AIData.currentGamePiece->getRow() + 2;
	for (BoardNode &node : gameData.nodes) {
		if (node.getRow() == forwardRow && node.getColumn() == leftCol
			&& node.getAssignment() == Util::PLAYER_ONE) {
			return true;
		}
	}
	return false;
}

bool AIManager::dangerDiagonalRight()
{
	int rightCol = AIData.currentGamePiece->getColumn() + 1;
	int forwardRow = AIData.currentGamePiece->getRow() + 2;
	for (BoardNode &node : gameData.nodes) {
		if (node.getRow() == forwardRow && node.getColumn() == rightCol
			&& node.getAssignment() == Util::PLAYER_ONE) {
			return true;
		}
	}
	return false;
}

bool AIManager::inDanger()
{
	return dangerDiagonalLeft() || dangerDiagonalRight() || dangerForwardLeft() || dangerForwardRight() || dangerForward();
}
