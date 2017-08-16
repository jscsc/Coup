#include "Kinematic.h"
#include "GameMath.h"
#include "SteeringOutput.h"

Kinematic::Kinematic() : position(0.0f, 0.0f), orientation(0.0f), velocity(0.0f, 0.0f), rotation(0.0f)
{
}

Kinematic::~Kinematic()
{
}

void Kinematic::update(const SteeringOutput & steering, const float deltaTime)
{
	// Update the position and orientation
	position += velocity * deltaTime;
	orientation += rotation * deltaTime;

	// Update the velocity and rotation
	velocity += steering.linear * deltaTime;
	rotation += steering.angular * deltaTime;

	// cap the velocity and rotation
	if (GameMath::mag(velocity) > MAX_SPEED)
	{
		GameMath::normalize(velocity);
		velocity *= MAX_SPEED;
	}
}

void Kinematic::update(const SteeringOutput &steering)
{
	// Update the position and orientation
	position += velocity;
	orientation += rotation;

	// Update the velocity and rotation
	velocity += steering.linear;
	rotation += steering.angular;

	// Cap the velocity and rotation
	if (GameMath::mag(velocity) > MAX_SPEED)
	{
		GameMath::normalize(velocity);
		velocity *= MAX_SPEED;
	}
}

void Kinematic::reset()
{
	position.x = 0;
	position.y = 0;
	orientation = 0;
	velocity.x = 0;
	velocity.y = 0;
	rotation = 0;
}
