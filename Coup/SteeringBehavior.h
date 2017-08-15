#pragma once
#include "SteeringOutput.h"

// Base abstract class for any Steering Behavior algorithm
class SteeringBehavior
{

public:

	// Constructor / Destructor
	SteeringBehavior();
	~SteeringBehavior();

	// Virtual function to run SteeringBehaviors
	virtual SteeringOutput getSteering() = 0;

};

