#pragma once
#include "Shape.h"
class ComplexShape : public Shape
{
private:
	bool setupVertexObjects(GLuint* VBO, GLuint* VAO) override;
	int Flags;
public:
	ComplexShape(GLuint* VBO, GLuint* VAO, int startingPosition, int count, int Flags);
	// Inherited via Shape
	virtual bool createShape() override;
	virtual bool deleteShape() override;
	virtual bool updateShape() override;
};

