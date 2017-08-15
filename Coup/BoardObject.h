#pragma once
#include "GameObject.h"
#include "RenderableObject.h"

// Class represenitng an object that is placable on the game board
class BoardObject : public RenderableObject
{
	// The row in which this object is located
	int row = 0;

	// The column in which the object is located
	int column = 0;

public:

	// Constrctors / Destructors
	BoardObject();
	BoardObject(int row, int column);
	~BoardObject();

	// Getters and Setters
	void setRow(int row);
	int getRow();
	void setColumn(int column);
	int getColumn();
};

