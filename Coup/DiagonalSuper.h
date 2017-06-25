#pragma once
#include "Movement.h"
class DiagonalSuper : public Movement
{

	bool validatePlayerOne(int nodeRow, int nodeColumn, int pieceRow, int pieceColumn) override;
	bool validatePlayerTwo(int nodeRow, int nodeColumn, int pieceRow, int pieceColumn) override;

public:
	DiagonalSuper(sf::Texture &baseTexture, sf::Texture &selectedTexture);
	~DiagonalSuper();
};

