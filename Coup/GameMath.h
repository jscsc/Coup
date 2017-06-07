#pragma once

#define _USE_MATH_DEFINES
#include <SFML/System.hpp>
#include <cmath>
class GameMath
{

public:
	// Call these functions at any time in the game logic
	static float mag(sf::Vector2f vector2D);

	static void normalize(sf::Vector2f &vector2D);

	static float radiansToDegrees(float radians);

private:
	// Disallow creating an instance of this object
	GameMath();
	~GameMath();
};

