#include "Arrive.h"
#include <iostream>
#include "GameMath.h"

Arrive::Arrive(Kinematic &character, Kinematic &target, float maxAcceleration, float maxSpeed, float targetRadius, float slowRadius)
	: character(character), target(target), maxAcceleration(maxAcceleration), maxSpeed(maxSpeed), targetRadius(targetRadius), slowRadius(slowRadius)
{
}

Arrive::Arrive() : character(Kinematic()), target(Kinematic())
{
}

Arrive::~Arrive()
{
}

SteeringOutput Arrive::getSteering()
{

	// Create the structure to hold our output
	SteeringOutput steering = SteeringOutput();

	// Get the direction to the target
	sf::Vector2f direction = target.position - character.position;

	float distance = GameMath::mag(direction);

	float targetSpeed;

	// Check if we are there, return blank steering
	if (distance < targetRadius)
		targetSpeed = 0;
	// If we are outside teh slowRadius, then go max speed
	else if (distance > slowRadius) {
		targetSpeed = maxSpeed;
		// Otherwise calculate a scaled speed
	} 
	else
		targetSpeed = maxSpeed * (distance / slowRadius);

	// The target velocity combines speed and direction
	sf::Vector2f targetVelocity = direction;
	GameMath::normalize(targetVelocity);
	targetVelocity *= targetSpeed;

	// Acceleration tries to get to the target velocity
	steering.linear = targetVelocity - character.velocity;
	steering.linear /= TIME_TO_TARGET;

	// Check if the acceleration is too fast
	if (GameMath::mag(steering.linear) > maxAcceleration)
	{
		GameMath::normalize(steering.linear);
		steering.linear *= maxAcceleration;
	}

	// Output the steering
	steering.angular = 0;
	return steering;
}

