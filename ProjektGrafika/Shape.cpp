#include "Shape.h"

Shape::Shape(int startingPosition,int count)
{
	this->startingPosition = (GLint)startingPosition;
	this->count = (GLsizei)count;
}
