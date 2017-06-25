#include "Diagonal.h"



bool Diagonal::validatePlayerOne(int nodeRow, int nodeColumn, int pieceRow, int pieceColumn)
{
	bool leftColSide = (nodeColumn == pieceColumn - 1);
	bool rightColSide = (nodeColumn == pieceColumn + 1);
	bool row = (nodeRow == pieceRow - 1);
	return row && (leftColSide || rightColSide);
}

bool Diagonal::validatePlayerTwo(int nodeRow, int nodeColumn, int pieceRow, int pieceColumn)
{
	bool rightColSide = (nodeColumn == pieceColumn - 1);
	bool leftColSide = (nodeColumn == pieceColumn + 1);
	bool row = (nodeRow == pieceRow + 1);
	return row && (leftColSide || rightColSide);
}


Diagonal::Diagonal(sf::Texture & baseTexture, sf::Texture & selectedTexture)
	: Movement(Util::DIAGONAL, baseTexture, selectedTexture)
{
	setCost(2);
}

Diagonal::~Diagonal()
{
}
