#include "GameOperation.h"
#include "Movement.h"
#include "Stay.h"
#include "Back.h"
#include "LeftOrRight.h"
#include "Diagonal.h"
#include "Super.h"
#include "BoardNode.h"
#include "PlayerData.h"
#include "GameData.h"
#include "GamePiece.h"
#include "GameMath.h"
#include "Textures.h"
#include <iostream>
#include <random>

Util::MovementType GameOperation::combineMovement(Util::MovementType currentType, Util::MovementType additionalType)
{
	return Util::MovementType();
}

Util::MovementType GameOperation::separateMovement(Util::MovementType currentType, Util::MovementType removalType)
{
	return Util::MovementType();
}

void GameOperation::validatePositionSetupBoard(std::vector<BoardNode>& nodes, PlayerData & playerData)
{
	int targetRow;

	if (playerData.type == Util::PLAYER_ONE)
		targetRow = 4;
	else
		targetRow = 0;

	for (BoardNode &node : nodes) {
		if (node.getRow() == targetRow && node.getAssignment() == Util::NEUTRAL)
			node.setValid(true);
		else
			node.setValid(false);
	}
}

void GameOperation::addMovement(PlayerData &playerData, Util::MovementType type)
{
	switch (type)
	{
		case Util::BACK:
			playerData.movements.push_back(new Back(playerData.textures.backTexture, playerData.textures.backSelectedTexture));
			break;
		case Util::STAY:
			playerData.movements.push_back(new Stay(playerData.textures.stayTexture, playerData.textures.staySelectedTexture));
			break;
		case Util::LEFT_OR_RIGHT:
			playerData.movements.push_back(new LeftOrRight(playerData.textures.leftOrRightTexture, playerData.textures.leftOrRightSelectedTexture));
			break;
		case Util::DIAGONAL:
			playerData.movements.push_back(new Diagonal(playerData.textures.diagonalTexture, playerData.textures.diagonalSelectedTexture));
			break;
		case Util::SUPER:
			playerData.movements.push_back(new Super(playerData.textures.superTexture, playerData.textures.superSelectedTexture));
			break;
		case Util::FORWARD:
			playerData.movements.push_back(new Movement(playerData.textures.backTexture, playerData.textures.backSelectedTexture));
			break;
		default:
			break;
	}


}

void GameOperation::resetBoard(std::vector<BoardNode>& nodes)
{
	for (BoardNode &node : nodes)
		node.setValid(false);
}

void GameOperation::validateBoard(PlayerData & playerData, GameData & gameData)
{
	if (playerData.currentGamePiece == nullptr) {
		resetBoard(gameData.nodes);
		return;
	}

	for (BoardNode &node : gameData.nodes)
		if (node.getAssignment() != playerData.type || playerData.currentMovement->getMovementType() == Util::STAY)
			node.setValid(playerData.currentMovement->validate(node, *playerData.currentGamePiece));
		else
			node.setValid(false);
}

void GameOperation::executeMovement(PlayerData & playerData, BoardNode & node)
{
	if (playerData.currentGamePiece == nullptr)
		return;

	playerData.currentGamePiece->setRow(node.getRow());
	playerData.currentGamePiece->setColumn(node.getColumn());
	playerData.currentGamePiece->setMovementTargetPosition(node.kinematic.position.x, node.kinematic.position.y);
	playerData.points -= playerData.currentMovement->getCost();
	playerData.currentMovement->setActive(false);
	playerData.ready = true;
	node.setAissignment(playerData.type);
}

void GameOperation::unassignNode(int row, int column, GameData & gameData)
{
	for (BoardNode &node : gameData.nodes) {
		if (node.getRow() == row && node.getColumn() == column) {
			node.setAissignment(Util::NEUTRAL);
			break;
		}
	}
}

bool GameOperation::piecesAssigned(PlayerData & playerData)
{
	return playerData.assignedPieces == playerData.pieces.size();
}

void GameOperation::switchTrun(GameData & gameData)
{
	if (gameData.currentTurn == Util::PLAYER_ONE)
		gameData.currentTurn = Util::PLAYER_TWO;
	else
		gameData.currentTurn = Util::PLAYER_ONE;
}

void GameOperation::pickRandomTurn(GameData & gameData)
{
	std::random_device randomDevice; // Obtain a random number from hardware
	std::mt19937 engine(randomDevice()); // seed the generator
	std::uniform_int_distribution<> distribution(0, 1); // define the range
	int randomInt = distribution(engine);

	if (randomInt == 0)
		gameData.currentTurn = Util::PLAYER_ONE;
	else
		gameData.currentTurn = Util::PLAYER_TWO;
}

void GameOperation::handlePlayerMovements(PlayerData & playerData)
{

	// move every active player piece
	for (GamePiece* piece : playerData.pieces)
		if (piece->isActive())
			piece->move();

	// check and see if any pieces are moving
	bool atleastOneMoveing = false;
	for (GamePiece* piece : playerData.pieces)
		if (piece->isActive() && GameMath::mag(piece->kinematic.velocity) > 0.0f)
			atleastOneMoveing = true;

	playerData.pieceMoving = atleastOneMoveing;
}

void GameOperation::setText(sf::Text & text, sf::Font & gameFont, int charSize, float x, float y, const std::string & message)
{
	text.setFont(gameFont);
	text.setString(message);
	text.setCharacterSize(charSize);
	text.setFillColor(sf::Color::Black);
	text.setPosition(sf::Vector2f(x, y));
}

bool GameOperation::piecesRemaining(PlayerData & playerData)
{
	for (GamePiece *piece : playerData.pieces)
		if (piece->isActive())
			return true;
	return false;
}

void GameOperation::centerText(sf::Text & text, float percentOfWidth, float percentOfHeight)
{
	float x = (1024 * percentOfWidth) - (text.getLocalBounds().width / 2.0f);
	float y = (768 * percentOfHeight) - (text.getLocalBounds().height / 2.0f);
	text.setPosition(x, y);
}

void GameOperation::centerTextX(sf::Text & text, float percentOfWidth)
{
	float x = (1024 * percentOfWidth) - (text.getLocalBounds().width / 2.0f);
	text.setPosition(x, text.getPosition().y);
}

void GameOperation::centerTextY(sf::Text & text, float percentOfHeight)
{
	float y = (768 * percentOfHeight) - (text.getLocalBounds().height / 2.0f);
	text.setPosition(text.getPosition().x, y);
}

GameOperation::GameOperation()
{
}

GameOperation::~GameOperation()
{
}