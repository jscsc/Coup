#pragma once
#include "Movement.h"
class LeftOrRight : public Movement
{

	bool validatePlayerOne(int nodeRow, int nodeColumn, int pieceRow, int pieceColumn) override;
	bool validatePlayerTwo(int nodeRow, int nodeColumn, int pieceRow, int pieceColumn) override;

public:
	LeftOrRight();
	~LeftOrRight();
};

