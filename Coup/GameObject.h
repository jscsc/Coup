#pragma once

#include "Kinematic.h"

class GameObject
{



public:

	// Every GameObject should have a Kinematic data structure
	Kinematic kinematic; // <--- This one

	GameObject();

	virtual ~GameObject() = 0;


	



};

