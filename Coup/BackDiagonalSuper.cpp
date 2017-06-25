#include "BackDiagonalSuper.h"



bool BackDiagonalSuper::validatePlayerOne(int nodeRow, int nodeColumn, int pieceRow, int pieceColumn)
{
	bool rightColSide = (nodeColumn == pieceColumn - 2);
	bool leftColSide = (nodeColumn == pieceColumn + 2);
	bool row = (nodeRow == pieceRow + 2);
	return row && (leftColSide || rightColSide);
}

bool BackDiagonalSuper::validatePlayerTwo(int nodeRow, int nodeColumn, int pieceRow, int pieceColumn)
{
	bool leftColSide = (nodeColumn == pieceColumn - 2);
	bool rightColSide = (nodeColumn == pieceColumn + 2);
	bool row = (nodeRow == pieceRow - 2);
	return row && (leftColSide || rightColSide);
}


BackDiagonalSuper::BackDiagonalSuper(sf::Texture & baseTexture, sf::Texture & selectedTexture)
	: Movement(Util::BACK_DIAGONAL_SUPER, baseTexture, selectedTexture)
{
	setCost(6);
}

BackDiagonalSuper::~BackDiagonalSuper()
{
}
