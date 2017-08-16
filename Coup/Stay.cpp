#include "Stay.h"

bool Stay::validatePlayerOne(int nodeRow, int nodeColumn, int pieceRow, int pieceColumn)
{
	return (nodeRow == pieceRow) && (nodeColumn == pieceColumn);
}

bool Stay::validatePlayerTwo(int nodeRow, int nodeColumn, int pieceRow, int pieceColumn)
{
	return (nodeRow == pieceRow) && (nodeColumn == pieceColumn);;
}

Stay::Stay(sf::Texture & baseTexture, sf::Texture & selectedTexture)
	: Movement(Util::STAY, baseTexture, selectedTexture)
{
	setCost(1);
}

Stay::~Stay()
{
}
