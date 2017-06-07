#include "Back.h"

bool Back::validatePlayerOne(int nodeRow, int nodeColumn, int pieceRow, int pieceColumn)
{
	return (nodeRow == pieceRow + 1) && (nodeColumn == pieceColumn);
}

bool Back::validatePlayerTwo(int nodeRow, int nodeColumn, int pieceRow, int pieceColumn)
{
	return (nodeRow == pieceRow - 1) && (nodeColumn == pieceColumn);;
}

Back::Back() : Movement(Util::BACK)
{
	setCost(1);
}


Back::~Back()
{
}
