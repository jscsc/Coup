#include "BoardObject.h"



BoardObject::BoardObject() : RenderableObject(), row(0), column(0)
{

}

BoardObject::BoardObject(int row, int column) : RenderableObject(), row(row), column(column)
{
}


BoardObject::~BoardObject()
{
}

void BoardObject::setRow(int row)
{
	this->row = row;
}

int BoardObject::getRow()
{
	return row;
}

void BoardObject::setColumn(int column)
{
	this->column = column;
}

int BoardObject::getColumn()
{
	return column;
}
