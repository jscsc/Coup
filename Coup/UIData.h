#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "MenuButton.h"
#include "ToggleButton.h"
#include "Util.h"
class Movement;
struct Textures;
struct UIData
{


	// Main Menu
	sf::Text title;
	sf::Text quitButton;
	sf::Text howToPlay;
	sf::Text playButton;
	sf::Text instruction1;
	sf::Text instruction2;
	sf::Text instruction3;

	// Ability Select
	sf::Text opponentScore;
	sf::Text pointsUsed;
	sf::Text playerScore;
	sf::Text currentRound;
	sf::Text readyButton;
	sf::Text resetSelectionButton;
	sf::Text stayCost;
	sf::Text leftOrRightCost;
	sf::Text backCost;
	sf::Text diagonalCost;
	sf::Text superCost;
	sf::Text assignedColor;
	sf::Text abilityChoice;

	// Position Setup
	sf::Text pickPositions;

	// Game Over
	sf::Text winner;
	sf::Text replayButton;
	sf::Text returnToMainMenuButton;

	// Multiple
	sf::CircleShape triangle;
	sf::Text exitButton;

	

	std::vector< Movement* > movementSelection;

	UIData(Textures &textures, sf::Font &gameFont);
	~UIData();
	void setTriangleColor(Util::PlayerType currentTurn);
	void resetAll();
};

