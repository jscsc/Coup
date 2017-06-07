#pragma once
#include "Movement.h"
class LeftOrRightSuper : public Movement
{

	bool validatePlayerOne(int nodeRow, int nodeColumn, int pieceRow, int pieceColumn) override;
	bool validatePlayerTwo(int nodeRow, int nodeColumn, int pieceRow, int pieceColumn) override;

public:
	LeftOrRightSuper();
	~LeftOrRightSuper();
};

