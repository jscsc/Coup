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
	//std::cout << playerData.pieceMoving << std::endl;
	if (gameData.currentTurn == playerData.type && !playerData.pieceMoving)
		selectState();
}

void PlayerManager::selectState()
{
	switch (gameData.currentGameState)
	{

		case Util::ABILITY_SETUP:
			handelPlayerAbilitySetup();
			break;
		case Util::POSITION_SETUP:
			handelPlayerPositionSetup();
			break;
		case Util::GAMEPLAY:
			handelPlayerGameplay();
			break;
		default:
			break;

	}
}

void PlayerManager::gameLogic()
{

	// move every active player piece
	for (GamePiece* piece : playerData.pieces)
		if (piece->isActive())
			piece->move();

	// check and see if any pieces are moving
	bool atleastOneMoveing = false;
	for (GamePiece* piece : playerData.pieces)
		if (piece->isActive() && GameMath::mag(piece->kinematic.velocity) > 0.0f)
			atleastOneMoveing = true;

	playerData.pieceMoving = atleastOneMoveing;


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

void PlayerManager::handelGameAbilitySetup()
{
	// If both players have made their selections, move to the next state
	if (playerData.ready == true && otherPlayerData.ready == true) {
		gameData.currentGameState = Util::POSITION_SETUP;
	}
}

void PlayerManager::handelGamePositionSetup()
{
	// If all pieces are assigned and no one is moving, go to gameplay state
	if (playerData.assignedPieces == playerData.pieces.size()
		&& otherPlayerData.assignedPieces == otherPlayerData.pieces.size()
		&& !playerData.pieceMoving && !otherPlayerData.pieceMoving) {
		gameData.currentGameState = Util::GAMEPLAY;
	} else if (playerData.ready == true && !playerData.pieceMoving) {
		// otherwise if the current player is done with their 
		if (playerData.type == Util::PLAYER_ONE)
			gameData.currentTurn = Util::PLAYER_TWO;
		else
			gameData.currentTurn = Util::PLAYER_ONE;
		playerData.ready = false;
	}
}

void PlayerManager::handelGameGameplay()
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

	// If a piece is off the board now, then that means they scored
	for (GamePiece * myPiece : playerData.pieces) {
		if (!myPiece->isOnBoard())
			playerData.score++;
	}

	//TODO end the game if no more pieces on board
}

void PlayerManager::handelPlayerAbilitySetup()
{
	
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

	if (UI.readyButton.rect.getGlobalBounds().contains(mousePosition)) {
		UI.readyButton.setToggled(!UI.readyButton.isToggled());
		return true;
	}

	return false;
}

bool PlayerManager::handelAbilitySetupResetButton()
{
	sf::Vector2f &mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
	sf::Mouse::getPosition(window);

	if (UI.resetSelectionButton.rect.getGlobalBounds().contains(mousePosition)) {
		playerData.movements.empty();
		playerData.points = 0;
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

		if (movement->rect.getGlobalBounds().contains(mousePosition)) {
			GameOperation::addMovement(playerData, movement->getMovementType());
			playerData.points += movement->getCost();
			return true;
		}

	}

	return false;
}

void PlayerManager::handelPlayerPositionSetup()
{
	// If we have already assigned all our pieces, no reason to be here
	if (playerData.assignedPieces == playerData.pieces.size()) {
		resetBoard();
		return;
	}

	// Show available spaces to move
	GameOperation::validatePositionSetupBoard(gameData.nodes, playerData);

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
			playerData.currentGamePiece->setRow(node.getRow());
			playerData.currentGamePiece->setColumn(node.getColumn());
			playerData.currentGamePiece->setMovementTargetPosition(node.kinematic.position.x, node.kinematic.position.y);
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
		if (movement->isActive() && movement->rect.getGlobalBounds().contains(mousePosition)) {
			if (playerData.currentMovement != nullptr)
				playerData.currentMovement->setSelected(false);
			playerData.currentMovement = movement;
			playerData.currentMovement->setSelected(true);
			validateBoard();
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
				resetBoard();
				// reduce player points based on movement cost
				playerData.points -= playerData.currentMovement->getCost();
				// deactive current movmenet
				playerData.currentMovement->setActive(false);
				//reset pointer
				playerData.currentMovement = nullptr;
				// set new row and col for game peice
				playerData.currentGamePiece->setRow(node.getRow());
				playerData.currentGamePiece->setColumn(node.getColumn());

				playerData.currentGamePiece->setMovementTargetPosition(node.kinematic.position.x, node.kinematic.position.y);
				// reset current game peice pointer
				playerData.currentGamePiece->setSelected(false);
				playerData.currentGamePiece = nullptr;

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
			resetBoard();
			for (Movement *movement : playerData.movements)
				if (movement->isActive())
					movement->setSelected(false);

			if (playerData.currentGamePiece != nullptr)
				playerData.currentGamePiece->setSelected(false);
			playerData.currentGamePiece = piece;
			playerData.currentGamePiece->setSelected(true);
			return true;
		}
	}
	return false;
}

void PlayerManager::validateBoard()
{
	if (playerData.currentGamePiece == nullptr) {
		resetBoard();
		return;
	}

	//std::cout << "This is in validate board , and the node we are at is row: " << playerData.currentGamePiece->getRow() << " and col: " << playerData.currentGamePiece->getColumn() << std::endl;

	for (BoardNode &node : gameData.nodes) {
		
		node.setValid( playerData.currentMovement->validate(node, *playerData.currentGamePiece));

	}
}

void PlayerManager::resetBoard()
{
	for (BoardNode &node : gameData.nodes)
		node.setValid(false);
}

void PlayerManager::render()
{

	switch (gameData.currentGameState)
	{

		case Util::ABILITY_SETUP:
			renderAbilitySetup();
			break;
		case Util::POSITION_SETUP:
			renderPositionSetup();
			break;
		case Util::GAMEPLAY:
			renderGameplay();
			break;
		default:
			break;

	}
	
}

void PlayerManager::renderAbilitySetup()
{
	// Render movments to select from
	float x = 300.0f;
	float y = 400.0f;
	for (Movement *movement : UI.movementSelection) {
		if (movement->isActive()) {
			movement->setPosition(x, y);
			movement->render(window);
			x += 100;
		}
	}

	// render ready button
	UI.readyButton.render(window);

	// render reset button
	UI.resetSelectionButton.render(window);

	// render current movements
	x = 300.0f;
	y = 700.0f;
	for (Movement *movement : playerData.movements) {
		if (movement->isActive()) {
			movement->setPosition(x, y);
			movement->render(window);
			x += 100;
		}
	}
}

void PlayerManager::renderPositionSetup()
{
	for (BoardNode node : gameData.nodes)
		node.render(window);

	for (GamePiece* piece : playerData.pieces)
		if (piece->isActive())
			piece->render(window);
}

void PlayerManager::renderGameplay()
{
	for (BoardNode node : gameData.nodes)
		node.render(window);

	for (GamePiece* piece : playerData.pieces)
		if (piece->isActive())
			piece->render(window);

	float x = 300.0f;
	float y = 700.0f;
	for (Movement *movement : playerData.movements) {
		if (movement->isActive()) {
			movement->setPosition(x, y);
			movement->render(window);
			x += 100;
		}
	}
}
