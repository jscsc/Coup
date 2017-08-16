#pragma once
#include <SFML/Graphics.hpp>

struct PlayerData;
struct GameData;
struct UIData;

// Class to manager overall game logic
class GameManager
{

	// Reference to player one's data
	PlayerData &playerOne;

	// Reference to player two's data
	PlayerData &playerTwo;

	// Reference to the overall game data
	GameData &gameData;

	// Reference to the UI data
	UIData &UI;

	// Window to render to
	sf::RenderWindow &window;

public:

	// Constrctors and Destructor
	GameManager(PlayerData &playerOne, PlayerData &playerTwo, GameData &gameData, UIData &UI, sf::RenderWindow &window);
	~GameManager();

	// Starts the flow of game logic for this iteration
	void gameLogic();

	// TODO re-spell handel to handle

	// Functions to handle various states of the game each iteration
	void handleGameMainMenu();
	void handleGameAbilitySetup();
	void handleGamePositionSetup();

	// Determines if the turn is complete for the character passed in
	void determineTurnComplete(PlayerData &playerData);

	// Functions to handel the game logic during the Gameplay state
	void handleGameGameplay();
	void handleGameGameOver();
	void handleGameRoundOver();
	void handleGameplayRules(PlayerData &playerData, PlayerData &otherPlayerData);
};