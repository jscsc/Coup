#include "BoardNode.h"
#include <iostream>


BoardNode::BoardNode() : BoardObject()
{

}

BoardNode::BoardNode(float x, float y, int row, int column, float size) : BoardObject(row, column),
valid(false), occupied(false), body(size)
{
	body.setFillColor(sf::Color::Blue);
	body.setOrigin(body.getRadius(), body.getRadius());
	kinematic.position.x = x;
	kinematic.position.y = y;
	body.setPosition(kinematic.position);
}


BoardNode::~BoardNode()
{

}

void BoardNode::setValid(bool valid)
{
	this->valid = valid;
	if (this->valid == true) {
		body.setFillColor(sf::Color::Green);
	} else {
		body.setFillColor(sf::Color::Blue);
	}
}

bool BoardNode::isValid()
{
	return valid;
}

void BoardNode::setOccupied(bool occupied)
{
	this->occupied = occupied;
}

bool BoardNode::isOccupied()
{
	return occupied;
}


void BoardNode::render(sf::RenderWindow &window)
{
	window.draw(body);
}