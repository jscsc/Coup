#pragma once
#include <SFML/Graphics.hpp>

struct PlayerData;
struct GameData;
struct UIData;
class GameManager
{

	PlayerData &playerOne;

	PlayerData &playerTwo;

	GameData &gameData;

	UIData &UI;

	sf::RenderWindow &window;

public:
	GameManager(PlayerData &playerOne, PlayerData &playerTwo, GameData &gameData, UIData &UI, sf::RenderWindow &window);
	~GameManager();

	void gameLogic();

	void handelGameMainMenu();
	void handelGameAbilitySetup();
	void handelGamePositionSetup();
	void determineTurnComplete(PlayerData &playerData);
	void handelGameGameplay();
	void handelGameGameOver();
	void handelGameRoundOver();
	void handelGameplayRules(PlayerData &playerData, PlayerData &otherPlayerData);
};

