#pragma once
#include "Movement.h"
class BackDiagonalSuper : public Movement
{

	bool validatePlayerOne(int nodeRow, int nodeColumn, int pieceRow, int pieceColumn) override;
	bool validatePlayerTwo(int nodeRow, int nodeColumn, int pieceRow, int pieceColumn) override;

public:
	BackDiagonalSuper(sf::Texture &baseTexture, sf::Texture &selectedTexture);
	~BackDiagonalSuper();
};

