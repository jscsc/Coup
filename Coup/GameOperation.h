#pragma once
#include "Util.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <string>
class Movement;
class BoardNode;
struct PlayerData;
struct GameData;
class GameOperation
{
public:

	static Util::MovementType combineMovement(Util::MovementType currentType, Util::MovementType additionalType);
	static Util::MovementType separateMovement(Util::MovementType currentType, Util::MovementType removalType);
	static void validatePositionSetupBoard(std::vector< BoardNode > &nodes, PlayerData &playerData);
	static void addMovement(PlayerData &playerData, Util::MovementType type);
	static void resetBoard(std::vector< BoardNode > &nodes);
	static void validateBoard(PlayerData &playerData, GameData &gameData);
	static void executeMovement(PlayerData &playerData, BoardNode &node);
	static void unassignNode(int row, int column, GameData &gameData);
	static bool piecesAssigned(PlayerData &playerData);
	static void switchTrun(GameData &gameData);
	static void pickRandomTurn(GameData &gameData);
	static void handelPlayerMovements(PlayerData &playerData);
	static void setText(sf::Text &text, sf::Font &gameFont, int charSize, float x, float y, const std::string &message);
	static bool piecesRemaining(PlayerData &playerData);


private:
	// Disallow creating an instance of this object
	GameOperation();
	~GameOperation();
};

