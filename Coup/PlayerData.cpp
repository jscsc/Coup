#include "PlayerData.h"
#include "GamePiece.h"
#include "Textures.h"

PlayerData::PlayerData(Util::PlayerType type, Textures &textures) : type(type), points(0), score(0),
assignedPieces(0), pieceMoving(false), ready(false), textures(textures), defaultMovement(textures.stayTexture, textures.staySelectedTexture)
{
	resetCurrentMovement();
	setupGamePieces();
	currentGamePiece = nullptr;
}

PlayerData::~PlayerData()
{
	pieces.clear();
	movements.clear();
}

void PlayerData::resetCurrentMovement()
{
	currentMovement = &defaultMovement;
}

void PlayerData::setupGamePieces()
{
	if (type == Util::PLAYER_ONE) {

		pieces.push_back(new GamePiece(type, 459, 668, -1, -1, 10));
		pieces.push_back(new GamePiece(type, 512, 668, -1, -1, 10));
		pieces.push_back(new GamePiece(type, 565, 668, -1, -1, 10));

	} else {

		pieces.push_back(new GamePiece(type, 459, 100, -1, -1, 10));
		pieces.push_back(new GamePiece(type, 512, 100, -1, -1, 10));
		pieces.push_back(new GamePiece(type, 565, 100, -1, -1, 10));

	}
}

void PlayerData::resetAll()
{
	points = 0;
	score = 0;
	assignedPieces = 0;
	pieceMoving = false;
	ready = false;
	resetCurrentMovement();
	currentGamePiece = nullptr;
	resetGamePieces();
	movements.clear();

}

void PlayerData::resetRound()
{
	points = 0;
	assignedPieces = 0;
	pieceMoving = false;
	ready = false;
	resetCurrentMovement();
	currentGamePiece = nullptr;
	resetGamePieces();
	movements.clear();
}

void PlayerData::resetGamePieces()
{
	float x = 459;
	float y;
	if (type == Util::PLAYER_ONE) {
		y = 700;
	} else {
		y = 100;
	}

	for (GamePiece *piece : pieces) {
		piece->setRow(-1);
		piece->setColumn(-1);
		piece->kinematic.reset();
		piece->setPosition(x, y);
		piece->setArriveTarget(x, y);
		piece->setActive(true);
		piece->setSelected(false);
		piece->setOnBoard(false);
		x += 53;
	}
}
