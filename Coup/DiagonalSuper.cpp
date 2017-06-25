#include "DiagonalSuper.h"



bool DiagonalSuper::validatePlayerOne(int nodeRow, int nodeColumn, int pieceRow, int pieceColumn)
{
	bool leftColSide = (nodeColumn == pieceColumn - 2);
	bool rightColSide = (nodeColumn == pieceColumn + 2);
	bool row = (nodeRow == pieceRow - 2);
	return row && (leftColSide || rightColSide);
}

bool DiagonalSuper::validatePlayerTwo(int nodeRow, int nodeColumn, int pieceRow, int pieceColumn)
{
	bool rightColSide = (nodeColumn == pieceColumn - 2);
	bool leftColSide = (nodeColumn == pieceColumn + 2);
	bool row = (nodeRow == pieceRow + 2);
	return row && (leftColSide || rightColSide);
}

DiagonalSuper::DiagonalSuper(sf::Texture & baseTexture, sf::Texture & selectedTexture)
	: Movement(Util::DIAGONAL_SUPER, baseTexture, selectedTexture)
{
	setCost(5);
}

DiagonalSuper::~DiagonalSuper()
{
}
