#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
class RenderableObject : public GameObject
{
public:

	virtual void render(sf::RenderWindow &window) = 0;
	RenderableObject();
	~RenderableObject();
};

