#include "GameManager.h"
#include "Movement.h"
#include "PlayerData.h"
#include "GameData.h"
#include "BoardNode.h"
#include "GamePiece.h"
#include "GameOperation.h"
#include "Diagonal.h"
#include "GameMath.h"

GameManager::GameManager(PlayerData & playerData, GameData & gameData, sf::RenderWindow &window) :
	playerData(playerData), gameData(gameData), window(window)
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

	movementMap[Util::DIAGONAL] = &Diagonal();

}

GameManager::~GameManager()
{
}

void GameManager::playerLogic()
{
	if (gameData.currentTurn == playerData.type && !playerData.pieceMoving)
		selectState();
}

void GameManager::selectState()
{
	switch (gameData.currentGameState)
	{

		case Util::SETUP:
			handelSetup();
			break;
		case Util::GAMEPLAY:
			handelGameplay();
			break;
		default:
			break;

	}
}

void GameManager::gameLogic()
{
	// move every active player piece
	for (GamePiece piece : playerData.pieces)
		if (piece.isActive())
			piece.move();

	// check and see if any pieces are moving
	bool atleastOneMoveing = false;
	for (GamePiece piece : playerData.pieces) 
		if (piece.isActive() && GameMath::mag(piece.kinematic.velocity) > 0.0f)
			atleastOneMoveing = true;

	playerData.pieceMoving = true;


}

void GameManager::handelSetup()
{

}

void GameManager::handelGameplay()
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

bool GameManager::handelAbilitySelection()
{
	sf::Vector2f &mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
	sf::Mouse::getPosition(window);

	for (Movement* movement : playerData.movements) {
		if (movement->rect.getGlobalBounds().contains(mousePosition)) {
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

bool GameManager::handelBoardNodeSelection()
{
	sf::Vector2f &mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
	sf::Mouse::getPosition(window);

	for (BoardNode &node : nodes) {
		if (node.body.getGlobalBounds().contains(mousePosition)) {
			if (playerData.currentGamePiece != nullptr && node.isValid()) {
				playerData.currentGamePiece->setArriveTarget(node.kinematic.position.x, node.kinematic.position.y);
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
				// reset current game peice pointer
				playerData.currentGamePiece->setActive(false);
				playerData.currentGamePiece = nullptr;

				return true;

			}
		}
	}
	return false;
}

bool GameManager::handelGamePieceSelection()
{
	sf::Vector2f &mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
	sf::Mouse::getPosition(window);

	for (GamePiece& piece : playerData.pieces) {
		if (piece.body.getGlobalBounds().contains(mousePosition)) {
			if (playerData.currentGamePiece != nullptr)
				playerData.currentGamePiece->setActive(false);
			playerData.currentGamePiece = &piece;
			playerData.currentGamePiece->setActive(true);
			return true;
		}
	}
	return false;
}

void GameManager::validateBoard()
{
	if (playerData.currentGamePiece == nullptr) {
		resetBoard();
		return;
	}

	for (BoardNode &node : nodes) {
		
		node.setValid( playerData.currentMovement->validate(node, *playerData.currentGamePiece));

	}
}

void GameManager::resetBoard()
{
	for (BoardNode &node : nodes)
		node.setValid(false);
}

void GameManager::render()
{
	
	for (BoardNode node : nodes)
		node.render(window);

	for (GamePiece piece : playerData.pieces)
		if (piece.isActive())
			piece.render(window);

	//float x = 300.0f;
	//float y = 700.0f;
	//for (Movement *movement : playerData.movements) {
		//if (movement->isActive()) {
			window.draw(playerData.movements[0]->rect);
		//}
	//}
}
