#pragma once
#include "Movement.h"
class Super : public Movement
{

	bool validatePlayerOne(int nodeRow, int nodeColumn, int pieceRow, int pieceColumn) override;
	bool validatePlayerTwo(int nodeRow, int nodeColumn, int pieceRow, int pieceColumn) override;

public:
	Super(sf::Texture &baseTexture, sf::Texture &selectedTexture);
	~Super();
};

