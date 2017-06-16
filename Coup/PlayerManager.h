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
	void gameLogic();

	void handelGameAbilitySetup();
	void handelGamePositionSetup();
	void handelGameGameplay();

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

	void validateBoard();
	void resetBoard();

	void render();
	void renderAbilitySetup();
	void renderPositionSetup();
	void renderGameplay();
};

