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
	: triangle(30, 3)
{
	// Instructions
	std::string instr = "                                     How To Play\n\n";
	instr = instr + "move game pieces to opposite end of the board to score\n\n";
	instr = instr + " use abilities to avoid and attack opponent game pieces\n\n";
	instr = instr + "     player with the most score after three rounds wins";

	GameOperation::setText(readyButton, gameFont, 24, 485.0f, 200.0f, "Ready");
	GameOperation::setText(resetSelectionButton, gameFont, 24, 485.0f, 300.0f, "Reset");

	GameOperation::setText(title, gameFont, 128, 370.0f, 100.0f, "Coup Stick");
	GameOperation::setText(playButton, gameFont, 24, 490.0f, 325.0f, "Play");
	GameOperation::setText(quitButton, gameFont, 24, 490.0f, 400.0f, "Exit");
	GameOperation::setText(howToPlay, gameFont, 24, 225.0f, 500.0f, "How To Play");
	GameOperation::setText(instruction1, gameFont, 24, 225.0f, 550.0f, "move game pieces to the opposite end of the board to score");
	GameOperation::setText(instruction2, gameFont, 24, 225.0f, 600.0f, "use abilities to avoid and attack opponent's game pieces");
	GameOperation::setText(instruction3, gameFont, 24, 225.0f, 650.0f, "player with the highest score after three rounds wins");

	GameOperation::setText(opponentScore, gameFont, 24, 800.0f, 50.0f, "Opt Score");
	GameOperation::setText(playerScore, gameFont, 24, 800.0f, 100.0f, "Player Score");
	GameOperation::setText(currentRound, gameFont, 24, 800.0f, 150.0f, "Round");
	GameOperation::setText(pointsUsed, gameFont, 24, 800.0f, 200.0f, "Points");

	GameOperation::setText(stayCost, gameFont, 24, 311.0f, 475.0f, "1");
	GameOperation::setText(leftOrRightCost, gameFont, 24, 411.0f, 475.0f, "1");
	GameOperation::setText(backCost, gameFont, 24, 511.0f, 475.0f, "2");
	GameOperation::setText(diagonalCost, gameFont, 24, 611.0f, 475.0f, "2");
	GameOperation::setText(superCost, gameFont, 24, 711.0f, 475.0f, "3");

	GameOperation::setText(abilityChoice, gameFont, 24, 50.0f, 690.0f, "Chosen:");
	GameOperation::setText(assignedColor, gameFont, 24, 50.0f, 50.0f, "Assigned Color : Red");

	GameOperation::setText(pickPositions, gameFont, 24, 50.0f, 690.0f, "Choose Positions");

	GameOperation::setText(winner, gameFont, 128, 430.0f, 100.0f, "Tie");
	GameOperation::setText(replayButton, gameFont, 24, 480.0f, 350.0f, "Replay");
	GameOperation::setText(returnToMainMenuButton, gameFont, 24, 460.0f, 400.0f, "Main Menu");

	GameOperation::setText(exitButton, gameFont, 24, 900.0f, 690.0f, "Quit");

	// Centering text
	GameOperation::centerTextX(title, .5f);
	GameOperation::centerTextX(playButton, .5f);
	GameOperation::centerTextX(quitButton, .5f);
	GameOperation::centerTextX(howToPlay, .5f);
	GameOperation::centerTextX(instruction1, .5f);
	GameOperation::centerTextX(instruction2, .5f);
	GameOperation::centerTextX(instruction3, .5f);

	GameOperation::centerTextX(replayButton, .5f);
	

	triangle.setFillColor(sf::Color(255, 51, 51));
	triangle.setPosition(sf::Vector2f(50.0f, 50.0f));

	movementSelection.push_back(new Stay(textures.stayTexture, textures.staySelectedTexture));
	movementSelection.push_back(new LeftOrRight(textures.leftOrRightTexture, textures.leftOrRightSelectedTexture));
	movementSelection.push_back(new Back(textures.backTexture, textures.backSelectedTexture));
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
		triangle.setFillColor(sf::Color(255, 51, 51));
	else
		triangle.setFillColor(sf::Color(0, 191, 255));
}

void UIData::resetAll()
{
	//readyButton.setToggled(false);
}
