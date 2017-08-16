#include "Super.h"

bool Super::validatePlayerOne(int nodeRow, int nodeColumn, int pieceRow, int pieceColumn)
{
	return (nodeRow == pieceRow - 2) && (nodeColumn == pieceColumn);
}

bool Super::validatePlayerTwo(int nodeRow, int nodeColumn, int pieceRow, int pieceColumn)
{
	return (nodeRow == pieceRow + 2) && (nodeColumn == pieceColumn);
}

Super::Super(sf::Texture & baseTexture, sf::Texture & selectedTexture)
	: Movement(Util::SUPER, baseTexture, selectedTexture)
{
	setCost(3);
}

Super::~Super()
{
}
