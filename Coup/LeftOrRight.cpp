#include "LeftOrRight.h"



bool LeftOrRight::validatePlayerOne(int nodeRow, int nodeColumn, int pieceRow, int pieceColumn)
{
	bool left = (nodeColumn == pieceColumn - 1) && (nodeRow == pieceRow);
	bool right = (nodeColumn == pieceColumn + 1) && (nodeRow == pieceRow);
	return left || right;
}

bool LeftOrRight::validatePlayerTwo(int nodeRow, int nodeColumn, int pieceRow, int pieceColumn)
{
	bool right = (nodeColumn == pieceColumn - 1) && (nodeRow == pieceRow);
	bool left = (nodeColumn == pieceColumn + 1) && (nodeRow == pieceRow);
	return left || right;
}

LeftOrRight::LeftOrRight() : Movement(Util::LEFT_OR_RIGHT)
{
	setCost(1);
}


LeftOrRight::~LeftOrRight()
{
}
