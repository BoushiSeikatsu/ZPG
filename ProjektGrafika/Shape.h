#pragma once
#include <GL/glew.h>
//Flags pro urceni jestli mame v poli hodnoty vrcholu, barev a textur, kdyby byly vsechny tri pak VERTICES | COLOR | TEXTURE
enum ATTRIBUTES
{
	VERTICES = 1,
	COLOR = 2,
	TEXTURE = 4
};

class Shape
{
protected:
	GLint startingPosition;
	GLsizei count;
	virtual bool setupVertexObjects(GLuint* VBO, GLuint* VAO) = 0;
public:
	Shape(int startingPosition,int count);
	virtual bool createShape() = 0;
	virtual bool deleteShape() = 0;
	virtual bool updateShape() = 0;
};

