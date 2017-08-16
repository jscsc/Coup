#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"

// Represents objects that can be rendered to the screen
class RenderableObject : public GameObject
{

public:

	// Renders this object to the given window
	virtual void render(sf::RenderWindow &window) = 0;

	// Constructor / Destructor
	RenderableObject();
	~RenderableObject();
};

