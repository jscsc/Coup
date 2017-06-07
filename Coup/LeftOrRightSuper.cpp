#include "LeftOrRightSuper.h"



bool LeftOrRightSuper::validatePlayerOne(int nodeRow, int nodeColumn, int pieceRow, int pieceColumn)
{
	bool left = (nodeColumn == pieceColumn - 2) && (nodeRow == pieceRow);
	bool right = (nodeColumn == pieceColumn + 2) && (nodeRow == pieceRow);
	return left || right;
}

bool LeftOrRightSuper::validatePlayerTwo(int nodeRow, int nodeColumn, int pieceRow, int pieceColumn)
{
	bool right = (nodeColumn == pieceColumn - 2) && (nodeRow == pieceRow);
	bool left = (nodeColumn == pieceColumn + 2) && (nodeRow == pieceRow);
	return left || right;
}

LeftOrRightSuper::LeftOrRightSuper() : Movement(Util::LEFT_OR_RIGHT_SUPER)
{
	setCost(4);
}


LeftOrRightSuper::~LeftOrRightSuper()
{
}
