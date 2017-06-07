#pragma once
class Ability
{

protected:
	int cost = 0;
	bool active;
	bool selected;

public:
	Ability();
	Ability(int cost);
	~Ability();
	int getCost();
	void setCost(int cost);
	bool isActive();
	void setActive(bool active);
	void setSelected(bool selected);
	bool isSelected();
};

