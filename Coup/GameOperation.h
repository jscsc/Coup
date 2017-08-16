#pragma once
#include "Util.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <string>
class Movement;
class BoardNode;
struct PlayerData;
struct GameData;

// Static class that holds various functions used through different locations in the game
class GameOperation
{

public:

	// Combines two movments into one, if it can
	static Util::MovementType combineMovement(Util::MovementType currentType, Util::MovementType additionalType);

	// Seperates one movment into two, if it can
	static Util::MovementType separateMovement(Util::MovementType currentType, Util::MovementType removalType);

	// Sets up the board so that a player can pick a starting location in the Position Setup game state
	static void validatePositionSetupBoard(std::vector< BoardNode > &nodes, PlayerData &playerData);

	// Adds a movment to the given playerData
	static void addMovement(PlayerData &playerData, Util::MovementType type);

	// Resets the board so that every node is not valid
	static void resetBoard(std::vector< BoardNode > &nodes);

	// Validates the given board based on the given playerData (That is, their current movement)
	static void validateBoard(PlayerData &playerData, GameData &gameData);

	// executes a the currenet Movement given playerData on the given BoardNode
	static void executeMovement(PlayerData &playerData, BoardNode &node);

	// unassign a particular BoardNode given it's postion and the GameData
	static void unassignNode(int row, int column, GameData &gameData);

	// Determines if all pieces have been assgined to the board for the given PlayerData
	static bool piecesAssigned(PlayerData &playerData);

	// Changes whos turn it is in the game
	static void switchTrun(GameData &gameData);

	// Picks a random turn to start the game off with
	static void pickRandomTurn(GameData &gameData);

	// Handeles moving active pieces on the game board (for every game loop iteration)
	static void handlePlayerMovements(PlayerData &playerData);

	// Sets the given test to the given message
	static void setText(sf::Text &text, sf::Font &gameFont, int charSize, float x, float y, const std::string &message);

	// Determines how many pieces are remaining on the game board for a particular player given PlayerData
	static bool piecesRemaining(PlayerData &playerData);

	// Centers given text
	static void centerText(sf::Text &text, float percentOfWidth, float percentOfHeight);

	// Centers the x-axis of given text
	static void centerTextX(sf::Text &text, float percentOfWidth);

	// Centers the y-axis of given text
	static void centerTextY(sf::Text &text, float percentOfHeight);

private:
	// Disallow creating an instance of this object
	GameOperation();
	~GameOperation();
};