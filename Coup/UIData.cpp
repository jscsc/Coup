#include "UIData.h"
#include "Movement.h"
#include "Stay.h"
#include "Back.h"
#include "LeftOrRight.h"
#include "Diagonal.h"
#include "Super.h"



UIData::UIData()
{
	movementSelection.push_back(new Stay());
	movementSelection.push_back(new Back());
	movementSelection.push_back(new LeftOrRight());
	movementSelection.push_back(new Diagonal());
	movementSelection.push_back(new Super());
}


UIData::~UIData()
{
	movementSelection.empty();
}
