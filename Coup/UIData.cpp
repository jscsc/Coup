#include "UIData.h"
#include "Movement.h"
#include "Stay.h"
#include "Back.h"
#include "LeftOrRight.h"
#include "Diagonal.h"
#include "Super.h"
#include "Textures.h"
#include "GameOperation.h"
#include <string>



UIData::UIData(Textures &textures, sf::Font &gameFont)
	: readyButton(500, 200, gameFont, "Ready"), resetSelectionButton(500, 300, gameFont, "Reset"), triangle(30, 3)
{
	GameOperation::setText(title, gameFont, 128, 375.0f, 100.0f, "Coup");
	
	GameOperation::setText(opponentScore, gameFont, 24, 750.0f, 50.0f, "OPt Score");

	GameOperation::setText(playerScore, gameFont, 24, 750.0f, 100.0f, "Player Score");

	GameOperation::setText(currentRound, gameFont, 24, 750.0f, 150.0f, "Round");

	GameOperation::setText(pointsUsed, gameFont, 24, 750.0f, 200.0f, "Points");

	GameOperation::setText(playButton, gameFont, 24, 500.0f, 350.0f, "Play");

	GameOperation::setText(quitButton, gameFont, 24, 500.0f, 400.0f, "Quit");

	GameOperation::setText(winner, gameFont, 128, 375.0f, 100.0f, "Winner");

	GameOperation::setText(replayButton, gameFont, 24, 500.0f, 350.0f, "Replay");

	GameOperation::setText(returnToMainMenuButton, gameFont, 24, 480.0f, 400.0f, "Main Menu");
	

	triangle.setFillColor(sf::Color::Red);
	triangle.setPosition(sf::Vector2f(50.0f, 50.0f));

	movementSelection.push_back(new Stay(textures.stayTexture, textures.staySelectedTexture));
	movementSelection.push_back(new Back(textures.backTexture, textures.backSelectedTexture));
	movementSelection.push_back(new LeftOrRight(textures.leftOrRightTexture, textures.leftOrRightSelectedTexture));
	movementSelection.push_back(new Diagonal(textures.diagonalTexture, textures.diagonalSelectedTexture));
	movementSelection.push_back(new Super(textures.superTexture, textures.superSelectedTexture));
}


UIData::~UIData()
{
	movementSelection.empty();
}

void UIData::setTriangleColor(Util::PlayerType currentTurn)
{
	if (currentTurn == Util::PLAYER_ONE)
		triangle.setFillColor(sf::Color::Red);
	else
		triangle.setFillColor(sf::Color::Blue);
}

void UIData::resetAll()
{
	readyButton.setToggled(false);
}
