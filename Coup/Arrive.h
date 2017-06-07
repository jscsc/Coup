#pragma once
#include "SteeringBehavior.h"
#include "Kinematic.h"
class Arrive : public SteeringBehavior
{

	

	// Holds the max acceleration and speed of the character
	float maxAcceleration;
	float maxSpeed;

	// holds the radis for arriving at the target
	float targetRadius;

	// Holds the radius for beginning the slow down
	float slowRadius;

	// Holds the time over which to achieve target speed
	const float TIME_TO_TARGET = 1.0f;

public:

	// Holds the kinematic data for the character and target
	Kinematic &character;
	Kinematic &target;

	Arrive(Kinematic &character, Kinematic &target, float maxAcceleration, float maxSpeed, float targetRadius, float slowRadius);
	Arrive();
	~Arrive();
	SteeringOutput getSteering() override;

};

