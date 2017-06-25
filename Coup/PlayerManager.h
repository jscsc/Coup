#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Util.h"

class Movement;
struct PlayerData;
struct GameData;
struct UIData;
class BoardNode;
class PlayerManager
{

	PlayerData &playerData;

	PlayerData &otherPlayerData;

	GameData &gameData;

	UIData &UI;

	sf::RenderWindow &window;



public:
	PlayerManager(PlayerData &playerData, PlayerData &otherPlayerData, GameData &gameData, UIData &UI, sf::RenderWindow &window);
	~PlayerManager();

	void playerLogic();
	void selectState();

	void handelPlayerMainMenu();
	bool handelMainMenuStartButton();
	bool handelMainMenuQuitButton();

	void handelPlayerAbilitySetup();
	bool handelAbilitySetupReadyButton();
	bool handelAbilitySetupResetButton();
	bool handelAbilitySetupAbilitySelection();

	void handelPlayerPositionSetup();
	bool handelPositionSetupGamePieceSelection();
	bool handelPositionSetupBoardNodeSelection();

	void handelPlayerGameplay();
	bool handelAbilitySelection();
	bool handelBoardNodeSelection();
	bool handelGamePieceSelection();

	void handelPlayerGameOver();
	bool handelGameOverReplayButton();
	bool handelGameOverMainMenuButton();
};

