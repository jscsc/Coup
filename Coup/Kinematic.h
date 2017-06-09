#pragma once

#include <SFML/System.hpp>

// Forward declaration for struct - the more you know!
struct SteeringOutput;
class Kinematic
{
	const float MAX_SPEED = 0.5f;

public:

	// A 2D Vector for the position of the kinematic
	sf::Vector2f position;

	// A single floating point value for the direction in which this kinematic is facing
	float orientation;

	// A 2D Vector for the linear velocity of this kinematic
	sf::Vector2f velocity;

	// The angular velocity of this kinematic (the radians per second the orientation is changing)
	float rotation;

	// Constructor
	Kinematic();

	// Destructor
	~Kinematic();

	// Update method using delta time
	void update(const SteeringOutput &steering, const float deltaTime);

	// Update method wihtout using delta time
	void update(const SteeringOutput &steering);

};

