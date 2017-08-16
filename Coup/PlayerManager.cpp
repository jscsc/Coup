#include <iostream>
#include "PlayerManager.h"
#include "Movement.h"
#include "PlayerData.h"
#include "GameData.h"
#include "UIData.h"
#include "BoardNode.h"
#include "GamePiece.h"
#include "GameOperation.h"
#include "GameMath.h"
#include "Stay.h"
#include "Back.h"
#include "LeftOrRight.h"
#include "Diagonal.h"
#include "Super.h"

PlayerManager::PlayerManager(PlayerData & playerData, PlayerData &otherPlayerData, GameData & gameData, UIData &UI, sf::RenderWindow &window) :
	playerData(playerData), otherPlayerData(otherPlayerData), gameData(gameData), UI(UI) ,window(window)
{
}

PlayerManager::~PlayerManager()
{
}

void PlayerManager::playerLogic()
{
	if ((gameData.currentTurn == playerData.type && !playerData.pieceMoving) 
		|| gameData.currentTurn == Util::NEUTRAL)
		selectState();
}

void PlayerManager::selectState()
{
	switch (gameData.currentGameState)
	{
		case Util::MAIN_MENU:
			handlePlayerMainMenu();
			break;
		case Util::ABILITY_SETUP:
			handlePlayerAbilitySetup();
			break;
		case Util::POSITION_SETUP:
			handlePlayerPositionSetup();
			break;
		case Util::GAMEPLAY:
			handlePlayerGameplay();
			break;
		case Util::GAME_OVER:
			handlePlayerGameOver();
			break;
		default:
			break;
	}
}

void PlayerManager::handlePlayerMainMenu()
{
	// Be sure the player actually clicked something;
	if (!gameData.mouseClicked || gameData.currentTurn != Util::NEUTRAL)
		return;

	if (handleMainMenuStartButton())
		return;

	if (handleMainMenuQuitButton())
		return;
}

bool PlayerManager::handleMainMenuStartButton()
{
	sf::Vector2f &mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
	sf::Mouse::getPosition(window);

	if (UI.playButton.getGlobalBounds().contains(mousePosition)) {
		playerData.ready = true;
		return true;
	}

	return false;
}

bool PlayerManager::handleMainMenuQuitButton()
{
	sf::Vector2f &mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
	sf::Mouse::getPosition(window);

	if (UI.quitButton.getGlobalBounds().contains(mousePosition)) {
		gameData.exitReady = true;
		return true;
	}

	return false;
}


void PlayerManager::handlePlayerAbilitySetup()
{
	// Be sure the player actually clicked something;
	if (!gameData.mouseClicked || gameData.currentTurn != Util::NEUTRAL)
		return;

	if (handleQuitMatch())
		return;
	
	if (handleAbilitySetupReadyButton())
		return;
	
	if (handleAbilitySetupResetButton())
		return;

	if (handleAbilitySetupAbilitySelection())
		return;
	
}

bool PlayerManager::handleAbilitySetupReadyButton()
{
	sf::Vector2f &mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
	sf::Mouse::getPosition(window);

	if (UI.readyButton.getGlobalBounds().contains(mousePosition) && playerData.points >= 4) {
		playerData.ready = !playerData.ready;
		return true;
	}

	return false;
}

bool PlayerManager::handleAbilitySetupResetButton()
{

	sf::Vector2f &mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
	sf::Mouse::getPosition(window);

	if (UI.resetSelectionButton.getGlobalBounds().contains(mousePosition)) {
		playerData.movements.clear();
		playerData.points = 0;
		playerData.ready = false;
		return true;
	}

	return false;
}

bool PlayerManager::handleAbilitySetupAbilitySelection()
{
	// If we already have too many abilities, don't add
	if (playerData.points >= 4)
		return false;

	sf::Vector2f &mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
	sf::Mouse::getPosition(window);

	for (Movement * movement : UI.movementSelection) {

		if (movement->movementSprite.getGlobalBounds().contains(mousePosition)) {
			if (playerData.points + movement->getCost() <= 4) {
				GameOperation::addMovement(playerData, movement->getMovementType());
				playerData.points += movement->getCost();
				return true;
			}
		}

	}

	return false;
}

void PlayerManager::handlePlayerPositionSetup()
{

	// If not our turn, don't be here
	if (gameData.currentTurn != playerData.type)
		return;

	if (handleQuitMatch())
		return;

	// If we have already assigned all our pieces, no reason to be here
	if (GameOperation::piecesAssigned(playerData)) {
		GameOperation::resetBoard(gameData.nodes);
		return;
	}

	// Show available spaces to move
	if (playerData.currentGamePiece != nullptr) {
		GameOperation::validatePositionSetupBoard(gameData.nodes, playerData);
		
	}

	if (!gameData.mouseClicked)
		return;

	if (handlePositionSetupGamePieceSelection())
		return;

	if (handlePositionSetupBoardNodeSelection())
		return;
}

bool PlayerManager::handlePositionSetupGamePieceSelection()
{
	sf::Vector2f &mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
	sf::Mouse::getPosition(window);

	for (GamePiece* piece : playerData.pieces) {
		if (piece->body.getGlobalBounds().contains(mousePosition) && !piece->isOnBoard()) {

			if (playerData.currentGamePiece != nullptr)
				playerData.currentGamePiece->setSelected(false);
			playerData.currentGamePiece = piece;
			playerData.currentGamePiece->setSelected(true);
			return true;
		}
	}
	return false;
}

bool PlayerManager::handlePositionSetupBoardNodeSelection()
{
	sf::Vector2f &mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
	sf::Mouse::getPosition(window);

	for (BoardNode &node : gameData.nodes) {
		if (node.body.getGlobalBounds().contains(mousePosition) && playerData.currentGamePiece != nullptr && node.isValid()) {
			GameOperation::resetBoard(gameData.nodes);
			
			GameOperation::executeMovement(playerData, node);
			playerData.currentGamePiece->setSelected(false);
			playerData.currentGamePiece->setOnBoard(true);
			playerData.currentGamePiece = nullptr;
			playerData.assignedPieces++;
			return true;
		}
	}
	return false;
}

void PlayerManager::handlePlayerGameplay()
{
	if (handleQuitMatch())
		return;

	// If not our turn, don't be here
	if (gameData.currentTurn != playerData.type)
		return;

	// Be sure the player actually clicked something;
	if (!gameData.mouseClicked)
		return;

	// Check and see if any nodes have been clicked on
	if (handleBoardNodeSelection())
		return;

	// Check and see if the player has updated their abilities
	if (handleAbilitySelection())
		return;

	// Check and see if the player updated their current gamePiece
	if (handleGamePieceSelection())
		return;

}

bool PlayerManager::handleAbilitySelection()
{
	if (playerData.currentGamePiece == nullptr)
		return false;

	sf::Vector2f &mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
	sf::Mouse::getPosition(window);

	for (Movement* movement : playerData.movements) {
		if (movement->isActive() && movement->movementSprite.getGlobalBounds().contains(mousePosition)) {

			// If this one is already selected, unselect and set default movmenet
			if (movement->isSelected()) {
				movement->setSelected(false);
				playerData.resetCurrentMovement();
				GameOperation::validateBoard(playerData, gameData);
				return true;
			}

			// If this movment is not selected, select it
			if (playerData.currentMovement != nullptr)
				playerData.currentMovement->setSelected(false);
			playerData.currentMovement = movement;
			playerData.currentMovement->setSelected(true);
			GameOperation::validateBoard(playerData, gameData);
			return true;
		}
	}
	return false;
}

bool PlayerManager::handleBoardNodeSelection()
{
	sf::Vector2f &mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
	sf::Mouse::getPosition(window);

	for (BoardNode &node : gameData.nodes) {
		if (node.body.getGlobalBounds().contains(mousePosition)) {
			if (playerData.currentGamePiece != nullptr && node.isValid()) {
				// TODO set up node references in gamepieces
				GameOperation::resetBoard(gameData.nodes);
				GameOperation::unassignNode(playerData.currentGamePiece->getRow(), playerData.currentGamePiece->getColumn(), gameData);
				GameOperation::executeMovement(playerData, node);
				playerData.currentGamePiece->setSelected(false);
				playerData.currentGamePiece->setOnBoard(true);
				playerData.currentGamePiece = nullptr;
				playerData.assignedPieces++;
				return true;

			}
		}
	}
	return false;
}

bool PlayerManager::handleGamePieceSelection()
{

	sf::Vector2f &mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
	sf::Mouse::getPosition(window);

	for (GamePiece* piece : playerData.pieces) {
		if (piece->body.getGlobalBounds().contains(mousePosition) && piece->isActive()) {
			// TODO seperate these into a function
			// Clear any selected movements
			GameOperation::resetBoard(gameData.nodes);
			for (Movement *movement : playerData.movements)
				if (movement->isActive())
					movement->setSelected(false);

			// Set default movement
			playerData.resetCurrentMovement();

			if (playerData.currentGamePiece != nullptr)
				playerData.currentGamePiece->setSelected(false);
			playerData.currentGamePiece = piece;
			playerData.currentGamePiece->setSelected(true);

			GameOperation::validateBoard(playerData, gameData);
			return true;
		}
	}
	return false;
}

void PlayerManager::handlePlayerGameOver()
{
	// Be sure the player actually clicked something;
	if (!gameData.mouseClicked || gameData.currentTurn != Util::NEUTRAL)
		return;

	if (handleGameOverReplayButton())
		return;

	if (handleGameOverMainMenuButton())
		return;
}

bool PlayerManager::handleGameOverReplayButton()
{
	sf::Vector2f &mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
	sf::Mouse::getPosition(window);

	if (UI.replayButton.getGlobalBounds().contains(mousePosition)) {
		playerData.ready = true;
		return true;
	}

	return false;
}

bool PlayerManager::handleGameOverMainMenuButton()
{
	sf::Vector2f &mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
	sf::Mouse::getPosition(window);

	if (UI.returnToMainMenuButton.getGlobalBounds().contains(mousePosition)) {
		gameData.exitReady = true;
		return true;
	}

	return false;
}

bool PlayerManager::handleQuitMatch()
{
	if (!gameData.mouseClicked)
		return false;

	sf::Vector2f &mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
	sf::Mouse::getPosition(window);

	if (UI.exitButton.getGlobalBounds().contains(mousePosition)) {
		gameData.exitReady = true;
		return true;
	}

	return false;
}