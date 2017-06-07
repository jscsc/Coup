#pragma once

#include "SteeringOutput.h"
class SteeringBehavior
{

public:
	SteeringBehavior();
	~SteeringBehavior();
	virtual SteeringOutput getSteering() = 0;

};

