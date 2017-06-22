#include "Renderer.h"
#include "PlayerData.h"
#include "GameData.h"
#include "UIData.h"
#include "BoardNode.h"
#include "GamePiece.h"
#include <iostream>


Renderer::Renderer(PlayerData & playerData, PlayerData &otherPlayerData, GameData & gameData, UIData & UI, sf::RenderWindow & window) :
	playerData(playerData), otherPlayerData(otherPlayerData), gameData(gameData), UI(UI), window(window)
{

}

Renderer::~Renderer()
{
}

void Renderer::render()
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

void Renderer::renderAbilitySetup()
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

void Renderer::renderPositionSetup()
{
	for (BoardNode &node : gameData.nodes)
			node.render(window);

	for (GamePiece* piece : playerData.pieces)
		if (piece->isActive())
			piece->render(window);

	for (GamePiece* piece : otherPlayerData.pieces)
		if (piece->isActive())
			piece->render(window);
}

void Renderer::renderGameplay()
{
	for (BoardNode &node : gameData.nodes)
		node.render(window);

	for (GamePiece* piece : playerData.pieces)
		if (piece->isActive())
			piece->render(window);

	for (GamePiece* piece : otherPlayerData.pieces)
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
