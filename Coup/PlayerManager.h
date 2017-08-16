#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Util.h"

class Movement;
struct PlayerData;
struct GameData;
struct UIData;
class BoardNode;

// Class to handle the player logic 
class PlayerManager
{

	// Reference to player one's data 
	PlayerData &playerData;

	// Reference to player two's data
	PlayerData &otherPlayerData;

	// Reference to the overall game data
	GameData &gameData;

	// Reference to the UI data
	UIData &UI;

	// Window to render to
	sf::RenderWindow &window;

public:

	// Constrctor and Destructor
	PlayerManager(PlayerData &playerData, PlayerData &otherPlayerData, GameData &gameData, UIData &UI, sf::RenderWindow &window);
	~PlayerManager();

	// Functions to start the flow of player logic for this iteration
	void playerLogic();
	void selectState();

	// Functions to handel player logic in the Main Menu state
	void handlePlayerMainMenu();
	bool handleMainMenuStartButton();
	bool handleMainMenuQuitButton();

	// Functions to handel player logic in the Ability Setup state
	void handlePlayerAbilitySetup();
	bool handleAbilitySetupReadyButton();
	bool handleAbilitySetupResetButton();
	bool handleAbilitySetupAbilitySelection();

	// Functions to handel player logic in the Position Setup state
	void handlePlayerPositionSetup();
	bool handlePositionSetupGamePieceSelection();
	bool handlePositionSetupBoardNodeSelection();

	// Functions to handel player logic in the Gameplay state
	void handlePlayerGameplay();
	bool handleAbilitySelection();
	bool handleBoardNodeSelection();
	bool handleGamePieceSelection();

	// Functions to handel player logic in the Game Over state
	void handlePlayerGameOver();
	bool handleGameOverReplayButton();
	bool handleGameOverMainMenuButton();

	// Handles qutting the game
	bool handleQuitMatch();
};

