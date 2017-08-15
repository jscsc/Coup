#pragma once

// Base class for any player ability in the game
class Ability
{

protected:
	// How much it costs to use this ability
	int cost = 0;

	// Whether or not this ability is active (can be used)
	bool active;

	// Whether or not this ability is selected (will be used)
	bool selected;

public:
	// Constructors / Destructors
	Ability();
	Ability(int cost);
	~Ability();

	// Getter and Setters
	int getCost();
	void setCost(int cost);
	bool isActive();
	void setActive(bool active);
	void setSelected(bool selected);
	bool isSelected();
};

