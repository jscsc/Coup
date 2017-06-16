#include "GameManager.h"
#include "PlayerData.h"
#include "GameData.h"
#include "UIData.h"
#include "BoardNode.h"
#include "GamePiece.h"




GameManager::GameManager(PlayerData & playerOne, PlayerData & playerTwo, GameData & gameData, UIData & UI, sf::RenderWindow & window)
	: playerOne(playerOne), playerTwo(playerTwo), gameData(gameData), UI(UI), window(window)
{
}

GameManager::~GameManager()
{
}

void GameManager::gameLogic()
{
	if (gameData.currentTurn == Util::PLAYER_ONE) {
		selectGameState(playerOne);
	} else {
		selectGameState(playerTwo);
	}
}

void GameManager::selectGameState(PlayerData & playerData)
{
	switch (gameData.currentGameState)
	{

		case Util::ABILITY_SETUP:
			handelGameAbilitySetup(playerData);
			break;
		case Util::POSITION_SETUP:
			handelGamePositionSetup(playerData);
			break;
		case Util::GAMEPLAY:
			handelGameGameplay(playerData);
			break;
		default:
			break;

	}
}

void GameManager::handelGameAbilitySetup(PlayerData & playerData)
{
	// If both players have made their selections, move to the next state
	if (playerOne.ready == true && playerTwo.ready == true) {
		gameData.currentGameState = Util::POSITION_SETUP;
	}
}

void GameManager::handelGamePositionSetup(PlayerData & playerData)
{
	
}

void GameManager::handelGameGameplay(PlayerData & playerData)
{

}

void GameManager::render()
{
	if (gameData.currentTurn == Util::PLAYER_ONE) {
		selectRenderState(playerOne);
	}
	else {
		selectRenderState(playerTwo);
	}
}

void GameManager::selectRenderState(PlayerData & playerData)
{
	switch (gameData.currentGameState)
	{

		case Util::ABILITY_SETUP:
			renderAbilitySetup(playerData);
			break;
		case Util::POSITION_SETUP:
			renderPositionSetup(playerData);
			break;
		case Util::GAMEPLAY:
			renderGameplay(playerData);
			break;
		default:
			break;

	}
}

void GameManager::renderAbilitySetup(PlayerData & playerData)
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

void GameManager::renderPositionSetup(PlayerData & playerData)
{
	for (BoardNode node : gameData.nodes)
		node.render(window);

	for (GamePiece* piece : playerData.pieces)
		if (piece->isActive())
			piece->render(window);
}

void GameManager::renderGameplay(PlayerData & playerData)
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

