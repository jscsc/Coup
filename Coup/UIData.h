#pragma once
#include <vector>
#include "MenuButton.h"
#include "ToggleButton.h"
class Movement;
struct UIData
{
	ToggleButton readyButton;

	MenuButton resetSelectionButton;

	std::vector< Movement* > movementSelection;

	UIData();
	~UIData();
};

