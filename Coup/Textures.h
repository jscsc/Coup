#pragma once
#include <SFML/Graphics.hpp>
struct Textures
{

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

