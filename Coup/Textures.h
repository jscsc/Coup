#pragma once
#include <SFML/Graphics.hpp>

// Struct to hold Textures used in the game
struct Textures
{
	// Textures for the different Movement abilities
	sf::Texture backTexture;
	sf::Texture backSelectedTexture;

	sf::Texture stayTexture;
	sf::Texture staySelectedTexture;

	sf::Texture leftOrRightTexture;
	sf::Texture leftOrRightSelectedTexture;

	sf::Texture diagonalTexture;
	sf::Texture diagonalSelectedTexture;

	sf::Texture superTexture;
	sf::Texture superSelectedTexture;

	Textures();
	~Textures();
};

