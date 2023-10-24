#pragma once
#include "Shape.h"
class Rectangle : public Shape
{
private:
	bool setupVertexObjects(GLuint* VBO, GLuint* VAO) override;
	int Flags;
	bool verticesSetup = false;
public:
	Rectangle(GLuint* VBO, GLuint* VAO, int startingPosition, int count, int Flags);
	bool createShape() override;
	bool deleteShape() override;
	bool updateShape() override;
};

