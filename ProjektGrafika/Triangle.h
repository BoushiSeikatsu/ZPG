#pragma once
#include "Shape.h"
class Triangle : public Shape
{
private:
	bool setupVertexObjects(GLuint* VBO, GLuint* VAO) override;
	int Flags;
public:
	Triangle(GLuint* VBO, GLuint* VAO, int startingPosition, int count, int Flags);
	bool createShape() override;
	bool deleteShape() override;
	bool updateShape() override;
};

