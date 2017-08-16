#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "MenuButton.h"
#include "ToggleButton.h"
#include "Util.h"
class Movement;
struct Textures;

// Struct holding all the relevant data and objects relating to UI
struct UIData
{


	// Main Menu items
	sf::Text title;
	sf::Text quitButton;
	sf::Text howToPlay;
	sf::Text playButton;
	sf::Text instruction1;
	sf::Text instruction2;
	sf::Text instruction3;

	// Ability Select items
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

	// Position Setup items
	sf::Text pickPositions;

	// Game Over items
	sf::Text winner;
	sf::Text replayButton;
	sf::Text returnToMainMenuButton;

	// Multiple items
	sf::CircleShape triangle;
	sf::Text exitButton;

	// List holding the movements to select from in the Ability Selection Menu
	std::vector< Movement* > movementSelection;

	// Constructor / Destructor
	UIData(Textures &textures, sf::Font &gameFont);
	~UIData();

	// Sets the color of the Triangle indecating whos turn it is
	void setTriangleColor(Util::PlayerType currentTurn);

	// Resets all UI elements
	void resetAll();
};

