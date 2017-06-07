#include "Stay.h"



bool Stay::validatePlayerOne(int nodeRow, int nodeColumn, int pieceRow, int pieceColumn)
{
	return (nodeRow == pieceRow) && (nodeColumn == pieceColumn);
}

bool Stay::validatePlayerTwo(int nodeRow, int nodeColumn, int pieceRow, int pieceColumn)
{
	return (nodeRow == pieceRow) && (nodeColumn == pieceColumn);;
}

Stay::Stay() : Movement(Util::STAY)
{
}


Stay::~Stay()
{
}
