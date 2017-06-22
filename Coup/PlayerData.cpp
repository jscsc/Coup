#include "PlayerData.h"
#include "GamePiece.h"

PlayerData::PlayerData() : type(Util::PlayerType::PLAYER_ONE), points(0), score(0),
assignedPieces(0), pieceMoving(false), ready(false)
{
	resetCurrentMovement();
	setupGamePieces();
	currentGamePiece = nullptr;
}


PlayerData::PlayerData(Util::PlayerType type) : type(type), points(0), score(0),
assignedPieces(0), pieceMoving(false), ready(false)
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

		pieces.push_back(new GamePiece(type, 450, 700, -1, -1, 10));
		pieces.push_back(new GamePiece(type, 500, 700, -1, -1, 10));
		pieces.push_back(new GamePiece(type, 550, 700, -1, -1, 10));

	} else {

		pieces.push_back(new GamePiece(type, 450, 100, -1, -1, 10));
		pieces.push_back(new GamePiece(type, 500, 100, -1, -1, 10));
		pieces.push_back(new GamePiece(type, 550, 100, -1, -1, 10));

	}
}
