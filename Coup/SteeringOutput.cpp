#include "SteeringOutput.h"



SteeringOutput::SteeringOutput() : position(0.0f, 0.0f), orientaion(0.0f), velocity(0.0f, 0.0f), rotation(0.0f), linear(0.0f, 0.0f), angular(0.0)
{
	
}


SteeringOutput::~SteeringOutput()
{
}

SteeringOutput SteeringOutput::operator+(const SteeringOutput other)
{
	SteeringOutput output = SteeringOutput();

	output.position = this->position + other.position;

	output.orientaion = this->orientaion + other.orientaion;

	output.velocity = this->velocity + other.velocity;

	output.rotation = this->rotation + other.rotation;

	output.linear = this->linear + other.linear;

	output.angular = this->angular + other.angular;

	return output;
}

