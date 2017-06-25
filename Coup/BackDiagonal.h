#pragma once
#include "Movement.h"
class BackDiagonal : public Movement
{

	bool validatePlayerOne(int nodeRow, int nodeColumn, int pieceRow, int pieceColumn) override;
	bool validatePlayerTwo(int nodeRow, int nodeColumn, int pieceRow, int pieceColumn) override;

public:
	BackDiagonal(sf::Texture &baseTexture, sf::Texture &selectedTexture);
	~BackDiagonal();
};

