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
			handelPlayerMainMenu();
			break;
		case Util::ABILITY_SETUP:
			handelPlayerAbilitySetup();
			break;
		case Util::POSITION_SETUP:
			handelPlayerPositionSetup();
			break;
		case Util::GAMEPLAY:
			handelPlayerGameplay();
			break;
		case Util::GAME_OVER:
			handelPlayerGameOver();
			break;
		default:
			break;

	}
}

void PlayerManager::handelPlayerMainMenu()
{

	// Be sure the player actually clicked something;
	if (!gameData.mouseClicked || gameData.currentTurn != Util::NEUTRAL)
		return;

	if (handelMainMenuStartButton())
		return;

	if (handelMainMenuQuitButton())
		return;

}

bool PlayerManager::handelMainMenuStartButton()
{
	sf::Vector2f &mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
	sf::Mouse::getPosition(window);

	if (UI.playButton.getGlobalBounds().contains(mousePosition)) {
		playerData.ready = true;
		return true;
	}

	return false;
}

bool PlayerManager::handelMainMenuQuitButton()
{
	sf::Vector2f &mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
	sf::Mouse::getPosition(window);

	if (UI.quitButton.getGlobalBounds().contains(mousePosition)) {
		gameData.exitReady = true;
		return true;
	}

	return false;
}


void PlayerManager::handelPlayerAbilitySetup()
{


	// Be sure the player actually clicked something;
	if (!gameData.mouseClicked || gameData.currentTurn != Util::NEUTRAL)
		return;

	//std::cout << "Got here" << std::endl;
	
	if (handelAbilitySetupReadyButton())
		return;
	
	if (handelAbilitySetupResetButton())
		return;

	if (handelAbilitySetupAbilitySelection())
		return;
	
}

bool PlayerManager::handelAbilitySetupReadyButton()
{
	sf::Vector2f &mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
	sf::Mouse::getPosition(window);


	if (UI.readyButton.text.getGlobalBounds().contains(mousePosition) && playerData.points >= 4) {
		UI.readyButton.setToggled(!UI.readyButton.isToggled());
		playerData.ready = !playerData.ready;
		return true;
	}

	return false;
}

bool PlayerManager::handelAbilitySetupResetButton()
{

	sf::Vector2f &mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
	sf::Mouse::getPosition(window);

	if (UI.resetSelectionButton.text.getGlobalBounds().contains(mousePosition)) {
		playerData.movements.clear();
		playerData.points = 0;
		playerData.ready = false;
		return true;
	}

	return false;
}

bool PlayerManager::handelAbilitySetupAbilitySelection()
{
	// If we already have too many abilities, don't add
	if (playerData.points >= 4)
		return false;

	// TODO look over again
	sf::Vector2f &mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
	sf::Mouse::getPosition(window);

	for (Movement * movement : UI.movementSelection) {

		if (movement->movementSprite.getGlobalBounds().contains(mousePosition)) {
			GameOperation::addMovement(playerData, movement->getMovementType());
			playerData.points += movement->getCost();
			return true;
		}

	}

	return false;
}

void PlayerManager::handelPlayerPositionSetup()
{
	// If not our turn, don't be here
	if (gameData.currentTurn != playerData.type)
		return;

	//std::cout << "Player pieces assigned: " << playerData.assignedPieces << std::endl;

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

	if (handelPositionSetupGamePieceSelection())
		return;

	if (handelPositionSetupBoardNodeSelection())
		return;
}

bool PlayerManager::handelPositionSetupGamePieceSelection()
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

bool PlayerManager::handelPositionSetupBoardNodeSelection()
{
	sf::Vector2f &mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
	sf::Mouse::getPosition(window);

	for (BoardNode &node : gameData.nodes) {
		if (node.body.getGlobalBounds().contains(mousePosition) && playerData.currentGamePiece != nullptr && node.isValid()) {
			GameOperation::resetBoard(gameData.nodes);
			
			//GameOperation::unassignNode(playerData.currentGamePiece->getRow(), playerData.currentGamePiece->getColumn(), gameData);
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

void PlayerManager::handelPlayerGameplay()
{
	// If not our turn, don't be here
	if (gameData.currentTurn != playerData.type)
		return;

	// Be sure the player actually clicked something;
	if (!gameData.mouseClicked)
		return;

	// Check and see if any nodes have been clicked on
	if (handelBoardNodeSelection())
		return;

	// Check and see if the player has updated their abilities
	if (handelAbilitySelection())
		return;

	// Check and see if the player updated their current gamePiece
	if (handelGamePieceSelection())
		return;

}

bool PlayerManager::handelAbilitySelection()
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

bool PlayerManager::handelBoardNodeSelection()
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

bool PlayerManager::handelGamePieceSelection()
{

	sf::Vector2f &mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
	sf::Mouse::getPosition(window);

	for (GamePiece* piece : playerData.pieces) {
		if (piece->body.getGlobalBounds().contains(mousePosition)) {
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

void PlayerManager::handelPlayerGameOver()
{
	// Be sure the player actually clicked something;
	if (!gameData.mouseClicked || gameData.currentTurn != Util::NEUTRAL)
		return;

	if (handelGameOverReplayButton())
		return;

	if (handelGameOverMainMenuButton())
		return;
}

bool PlayerManager::handelGameOverReplayButton()
{
	sf::Vector2f &mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
	sf::Mouse::getPosition(window);

	if (UI.replayButton.getGlobalBounds().contains(mousePosition)) {
		playerData.ready = true;
		return true;
	}

	return false;
}

bool PlayerManager::handelGameOverMainMenuButton()
{
	sf::Vector2f &mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
	sf::Mouse::getPosition(window);

	if (UI.returnToMainMenuButton.getGlobalBounds().contains(mousePosition)) {
		gameData.exitReady = true;
		return true;
	}

	return false;
}
