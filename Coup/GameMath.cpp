#include "GameMath.h"

float GameMath::mag(const sf::Vector2f vector2D)
{
	return sqrtf( (vector2D.x * vector2D.x) + (vector2D.y * vector2D.y) );
}

void GameMath::normalize(sf::Vector2f &vector2D)
{
	if (mag(vector2D) == 0)
		return;
	vector2D = vector2D / mag(vector2D);
}

float GameMath::radiansToDegrees(float radians)
{
	return static_cast<float>(radians * (180.0f / M_PI));
}

GameMath::GameMath()
{
}

GameMath::~GameMath()
{
}
