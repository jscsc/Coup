#include "Super.h"



bool Super::validatePlayerOne(int nodeRow, int nodeColumn, int pieceRow, int pieceColumn)
{
	return (nodeRow == pieceRow - 2) && (nodeColumn == pieceColumn);
}

bool Super::validatePlayerTwo(int nodeRow, int nodeColumn, int pieceRow, int pieceColumn)
{
	return (nodeRow == pieceRow + 2) && (nodeColumn == pieceColumn);
}

Super::Super() : Movement(Util::SUPER)
{
	setCost(3);
}


Super::~Super()
{
}
