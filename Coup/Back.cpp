#include "Back.h"

bool Back::validatePlayerOne(int nodeRow, int nodeColumn, int pieceRow, int pieceColumn)
{
	return (nodeRow == pieceRow + 1) && (nodeColumn == pieceColumn);
}

bool Back::validatePlayerTwo(int nodeRow, int nodeColumn, int pieceRow, int pieceColumn)
{
	return (nodeRow == pieceRow - 1) && (nodeColumn == pieceColumn);;
}

Back::Back(sf::Texture & baseTexture, sf::Texture & selectedTexture)
	: Movement(Util::BACK, baseTexture, selectedTexture)
{
	setCost(2);
}

Back::~Back()
{
}
