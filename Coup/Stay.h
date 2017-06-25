#pragma once
#include "Movement.h"
class Stay : public Movement
{

	bool validatePlayerOne(int nodeRow, int nodeColumn, int pieceRow, int pieceColumn) override;
	bool validatePlayerTwo(int nodeRow, int nodeColumn, int pieceRow, int pieceColumn) override;

public:
	Stay(sf::Texture &baseTexture, sf::Texture &selectedTexture);
	~Stay();
};

