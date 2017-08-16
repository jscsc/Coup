#pragma once

#define _USE_MATH_DEFINES
#include <SFML/System.hpp>
#include <cmath>

// Static class to hold math functions used by the game
class GameMath
{

public:
	// Call these functions at any time in the game logic

	// Gets the magnitude of the given vector2D
	static float mag(sf::Vector2f vector2D);

	// Normalizes the given vector2D
	static void normalize(sf::Vector2f &vector2D);

	// Converts the given radians to degrees
	static float radiansToDegrees(float radians);

private:
	// Disallow creating an instance of this object
	GameMath();
	~GameMath();
};

