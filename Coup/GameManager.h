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

	void selectGameState(PlayerData &playerData);

	void handelGameAbilitySetup(PlayerData &playerData);
	void handelGamePositionSetup(PlayerData &playerData);
	void handelGameGameplay(PlayerData &playerData);

	void render();
	void selectRenderState(PlayerData &playerData);

	void renderAbilitySetup(PlayerData &playerData);
	void renderPositionSetup(PlayerData &playerData);
	void renderGameplay(PlayerData &playerData);
};

