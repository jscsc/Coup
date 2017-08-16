#pragma once
#include "Kinematic.h"

// Base class representing GameObjects
class GameObject
{

public:

	// Every GameObject should have a Kinematic data structure
	Kinematic kinematic; // <--- This one

	// Constrctor / Destructors
	GameObject();
	virtual ~GameObject() = 0;

};

