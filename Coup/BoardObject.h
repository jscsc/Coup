#pragma once
#include "GameObject.h"
#include "RenderableObject.h"
class BoardObject : public RenderableObject
{

	int row = 0;

	int column = 0;

public:
	BoardObject();
	BoardObject(int row, int column);
	~BoardObject();
	void setRow(int row);
	int getRow();
	void setColumn(int column);
	int getColumn();
};

