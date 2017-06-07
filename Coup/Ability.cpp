#include "Ability.h"



Ability::Ability() : cost(0), active(true), selected(false)
{
}

Ability::Ability(int cost) : cost(cost), active(true), selected(false)
{
}

Ability::~Ability()
{
}

int Ability::getCost()
{
	return cost;
}

void Ability::setCost(int cost)
{
	this->cost = cost;
}

bool Ability::isActive()
{
	return active;
}

void Ability::setActive(bool active)
{
	this->active = active;
}

void Ability::setSelected(bool selected)
{
	this->selected = selected;
}

bool Ability::isSelected()
{
	return selected;
}
