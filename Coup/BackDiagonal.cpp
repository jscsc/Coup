#include "BackDiagonal.h"



bool BackDiagonal::validatePlayerOne(int nodeRow, int nodeColumn, int pieceRow, int pieceColumn)
{
	bool rightColSide = (nodeColumn == pieceColumn - 1);
	bool leftColSide = (nodeColumn == pieceColumn + 1);
	bool row = (nodeRow == pieceRow + 1);
	return row && (leftColSide || rightColSide);
}

bool BackDiagonal::validatePlayerTwo(int nodeRow, int nodeColumn, int pieceRow, int pieceColumn)
{
	bool leftColSide = (nodeColumn == pieceColumn - 1);
	bool rightColSide = (nodeColumn == pieceColumn + 1);
	bool row = (nodeRow == pieceRow - 1);
	return row && (leftColSide || rightColSide);
}

BackDiagonal::BackDiagonal(): Movement(Util::BACK_DIAGONAL)
{
	setCost(3);
}


BackDiagonal::~BackDiagonal()
{
}
