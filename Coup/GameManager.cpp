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
		case Util::MAIN_MENU:
			handelGameMainMenu();
			break;
		case Util::ABILITY_SETUP:
			handelGameAbilitySetup();
			break;
		case Util::POSITION_SETUP:
			handelGamePositionSetup();
			break;
		case Util::GAMEPLAY:
			handelGameGameplay();
			break;
		case Util::GAME_OVER:
			handelGameGameOver();
			break;
		default:
			break;

	}
}

void GameManager::handelGameMainMenu()
{
	// TODO: need to redo for mutiplayer
	if (playerOne.ready) {
		playerOne.ready = false;
		playerTwo.ready = false;
		gameData.currentGameState = Util::ABILITY_SETUP;
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
		playerOne.ready = false;
		playerTwo.ready = false;
	}
}

void GameManager::handelGameGameplay()
{
	// TODO restart game when no more player pieces on board
	if (!GameOperation::piecesRemaining(playerOne) || !GameOperation::piecesRemaining(playerTwo)) {
		handelGameRoundOver();
		return;
	}

	if (gameData.currentTurn == Util::PLAYER_ONE)
		handelGameplayRules(playerOne, playerTwo);
	else
		handelGameplayRules(playerTwo, playerOne);
}

void GameManager::handelGameGameOver()
{
	// TODO redo for multiplayer
	if (gameData.exitReady) {
		UI.resetAll();
		playerOne.resetAll();
		playerTwo.resetAll();
		gameData.resetAll();
	}
	else if (playerOne.ready) {
		UI.resetAll();
		playerOne.resetAll();
		playerTwo.resetAll();
		gameData.resetAll();
		gameData.currentGameState = Util::ABILITY_SETUP;
	}
}

void GameManager::handelGameRoundOver()
{
	// Count player one peices left
	for (GamePiece *piece : playerOne.pieces) {
		if (piece->isActive()) {
			playerOne.score++;
		}
	}

	// Count player two peices left
	for (GamePiece *piece : playerTwo.pieces) {
		if (piece->isActive()) {
			playerTwo.score++;
		}
	}

	gameData.round++;

	// If round is greater than limit, end the game, else reset round
	if (gameData.round >= 4) {
		playerOne.ready = false;
		playerTwo.ready = false;
		gameData.exitReady = false;
		gameData.currentTurn = Util::NEUTRAL;
		gameData.currentGameState = Util::GAME_OVER;
	} else {
		playerOne.resetRound();
		playerTwo.resetRound();
		gameData.resetRound();
	}
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
					otherPiece->setOnBoard(false);
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
		if (piece->isActive() && piece->getRow() == goalRow && !playerData.pieceMoving) {
			piece->setOnBoard(false);
			piece->setActive(false);
			GameOperation::unassignNode(piece->getRow(), piece->getColumn(), gameData);
			playerData.score++;
		}
	}

	determineTurnComplete(playerData);

}