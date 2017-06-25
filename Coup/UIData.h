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

	sf::Text title;

	sf::Text opponentScore;

	sf::Text pointsUsed;

	sf::Text playerScore;

	sf::Text currentRound;

	sf::Text playButton;

	sf::Text quitButton;

	sf::Text winner;

	sf::Text replayButton;

	sf::Text returnToMainMenuButton;

	ToggleButton readyButton;

	MenuButton resetSelectionButton;

	sf::CircleShape triangle;

	std::vector< Movement* > movementSelection;

	UIData(Textures &textures, sf::Font &gameFont);
	~UIData();
	void setTriangleColor(Util::PlayerType currentTurn);
	void resetAll();
};

