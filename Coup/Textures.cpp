#include "Textures.h"
#include <iostream>
#include<exception>


Textures::Textures()
{
	// Load Back Textures
	if (!backTexture.loadFromFile("Assets//Textures//Back.png"))
		throw "Texture failed to load";
	if (!backSelectedTexture.loadFromFile("Assets//Textures//BackSelected.png"))
		throw "Texture failed to load";

	// Load Stay Textures
	if (!stayTexture.loadFromFile("Assets//Textures//Stay.png"))
		throw "Texture failed to load";
	if (!staySelectedTexture.loadFromFile("Assets//Textures//StaySelected.png"))
		throw "Texture failed to load";

	// Load Left Or Right Textures
	if (!leftOrRightTexture.loadFromFile("Assets//Textures//LeftURight.png"))
		throw "Texture failed to load";
	if (!leftOrRightSelectedTexture.loadFromFile("Assets//Textures//LeftURightSelected.png")) {
		std::cout << "What is going on" << std::endl;
		throw "Texture failed to load";
	}

	// Load Diagonal Textures
	if (!diagonalTexture.loadFromFile("Assets//Textures//Diagonal.png"))
		throw "Texture failed to load";
	if (!diagonalSelectedTexture.loadFromFile("Assets//Textures//DiagonalSelected.png"))
		throw "Texture failed to load";

	// Load Super Textures
	if (!superTexture.loadFromFile("Assets//Textures//Super.png"))
		throw "Texture failed to load";
	if (!superSelectedTexture.loadFromFile("Assets//Textures//SuperSelected.png"))
		throw "Texture failed to load";
}

Textures::~Textures()
{
}
