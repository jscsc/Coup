#include "GameManager.h"
#include "PlayerData.h"
#include "GameData.h"
#include "UIData.h"
#include "BoardNode.h"
#include "GamePiece.h"
#include "GameOperation.h"
#include "GameMath.h"
#include <iostream>




GameManager::GameManager(PlayerData & playerOne, PlayerData & playerTwo, GameData & gameData, UIData & UI, sf::RenderWindow & window)
	: playerOne(playerOne), playerTwo(playerTwo), gameData(gameData), UI(UI), window(window)
{
}

GameManager::~GameManager()
{
}

void GameManager::gameLogic()
{
	GameOperation::handelPlayerMovements(playerOne);
	GameOperation::handelPlayerMovements(playerTwo);


	switch (gameData.currentGameState)
	{

		case Util::ABILITY_SETUP:
			handelGameAbilitySetup();
			break;
		case Util::POSITION_SETUP:
			handelGamePositionSetup();
			break;
		case Util::GAMEPLAY:
			handelGameGameplay();
			break;
		default:
			break;

	}
}

void GameManager::handelGameAbilitySetup()
{
	// If both players have made their selections, move to the next state
	if (playerOne.ready == true && playerTwo.ready == true) {
		gameData.currentGameState = Util::POSITION_SETUP;
		GameOperation::pickRandomTurn(gameData);
		playerOne.ready = false;
		playerTwo.ready = false;
	}
}

void GameManager::handelGamePositionSetup()
{

	if (GameOperation::piecesAssigned(playerOne) && GameOperation::piecesAssigned(playerTwo)) {
		GameOperation::switchTrun(gameData);
		gameData.currentGameState = Util::GAMEPLAY;
		playerOne.ready = false;
		playerTwo.ready = false;
		return;
	}

	if (gameData.currentTurn == Util::PLAYER_ONE)
		determineTurnComplete(playerOne);
	else
		determineTurnComplete(playerTwo);

}

void GameManager::determineTurnComplete(PlayerData & playerData)
{
	if (gameData.currentTurn == playerData.type && playerData.ready && !playerData.pieceMoving) {
		GameOperation::switchTrun(gameData);
		// This is what is breaking it
		playerOne.ready = false;
		playerTwo.ready = false;
	}
}

void GameManager::handelGameGameplay()
{
	// TODO restart game when no more player pieces on board

	if (gameData.currentTurn == Util::PLAYER_ONE)
		handelGameplayRules(playerOne, playerTwo);
	else
		handelGameplayRules(playerTwo, playerOne);
}

void GameManager::handelGameplayRules(PlayerData & playerData, PlayerData &otherPlayerData)
{
	// If we hit someone, handle it
	for (GamePiece * myPiece : playerData.pieces) {
		for (GamePiece * otherPiece : otherPlayerData.pieces) {
			if (myPiece->isActive() && otherPiece->isActive()) {
				sf::Vector2f direction = myPiece->kinematic.position - otherPiece->kinematic.position;
				float distance = GameMath::mag(direction);
				if (distance < 5.0f) {
					otherPiece->setActive(false);
				}
			}
		}
	}

	// If a game piece is on the last row for this player, log it as a score
	int goalRow;
	if (gameData.currentTurn == Util::PLAYER_ONE)
		goalRow = 0;
	else
		goalRow = 4;

	for (GamePiece* piece : playerData.pieces) {
		if (piece->getRow() == goalRow && !playerData.pieceMoving) {
			piece->setOnBoard(false);
			piece->setActive(false);
			playerData.score++;
		}
	}

	determineTurnComplete(playerData);

}






