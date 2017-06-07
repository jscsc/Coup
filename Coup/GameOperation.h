#pragma once
#include "Util.h"
class GameOperation
{
public:

	static Util::MovementType combineMovement(Util::MovementType currentType, Util::MovementType additionalType);
	static Util::MovementType separateMovement(Util::MovementType currentType, Util::MovementType removalType);


private:
	// Disallow creating an instance of this object
	GameOperation();
	~GameOperation();
};

