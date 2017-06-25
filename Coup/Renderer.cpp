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
		case Util::MAIN_MENU:
			//renderMainMenu();
			renderMainMenu();
			break;
		case Util::ABILITY_SETUP:
			renderAbilitySetup();
			break;
		case Util::POSITION_SETUP:
			renderPositionSetup();
			break;
		case Util::GAMEPLAY:
			renderGameplay();
			break;
		case Util::GAME_OVER:
			renderGameOver();
			break;
		default:
			break;

	}
}

void Renderer::renderMainMenu()
{
	// render title
	window.draw(UI.title);

	// Render Play and Quit Options
	window.draw(UI.playButton);
	window.draw(UI.quitButton);
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

	// Render Scores and round
	UI.playerScore.setString("Red Score: " + std::to_string(playerData.score));
	UI.opponentScore.setString("Blue Score: " + std::to_string(otherPlayerData.score));
	UI.currentRound.setString("Round: " + std::to_string(gameData.round) + " out of 3");
	UI.pointsUsed.setString("Points: " + std::to_string(playerData.points) + " out of 4");
	window.draw(UI.playerScore);
	window.draw(UI.opponentScore);
	window.draw(UI.currentRound);
	window.draw(UI.pointsUsed);
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

	// Render player turn
	UI.setTriangleColor(gameData.currentTurn);
	window.draw(UI.triangle);

	// Render Scores and round
	UI.playerScore.setString("Red Score: " + std::to_string(playerData.score));
	UI.opponentScore.setString("Blue Score: " + std::to_string(otherPlayerData.score));
	UI.currentRound.setString("Round: " + std::to_string(gameData.round) + " out of 3");
	window.draw(UI.playerScore);
	window.draw(UI.opponentScore);
	window.draw(UI.currentRound);
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

	// Render player turn
	UI.setTriangleColor(gameData.currentTurn);
	window.draw(UI.triangle);

	// Render Scores and round
	UI.playerScore.setString("Red Score: " + std::to_string(playerData.score));
	UI.opponentScore.setString("Blue Score: " + std::to_string(otherPlayerData.score));
	UI.currentRound.setString("Round: " + std::to_string(gameData.round) + " out of 3");
	window.draw(UI.playerScore);
	window.draw(UI.opponentScore);
	window.draw(UI.currentRound);
}

void Renderer::renderGameOver()
{
	// Render Winner
	if (playerData.score > otherPlayerData.score) {
		UI.winner.setString("Winner");
		UI.winner.setPosition(sf::Vector2f(330.0f, 100.0f));
	} else if (playerData.score > otherPlayerData.score) {
		UI.winner.setString("Loser");
		UI.winner.setPosition(sf::Vector2f(375.0f, 100.0f));
	} else {
		UI.winner.setString("Tie");
		UI.winner.setPosition(sf::Vector2f(450.0f, 100.0f));
	}


	window.draw(UI.winner);

	// Render replay and Main Menu Buttons
	window.draw(UI.replayButton);
	window.draw(UI.returnToMainMenuButton);
}
