#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Util.h"
class Movement;
struct PlayerData;
struct GameData;
class BoardNode;
class GameManager
{

	PlayerData &playerData;

	GameData &gameData;

	sf::RenderWindow &window;

	std::vector< BoardNode > nodes;

	std::map<Util::MovementType, Movement*> movementMap;

public:
	GameManager(PlayerData &playerData, GameData &gameData, sf::RenderWindow &window);
	~GameManager();

	void playerLogic();
	void selectState();
	void gameLogic();
	void handelSetup();
	void handelGameplay();
	bool handelAbilitySelection();
	bool handelBoardNodeSelection();
	bool handelGamePieceSelection();
	void validateBoard();
	void resetBoard();
	void render();
};

