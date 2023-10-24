#pragma once
#include "Shape.h"
#include <vector>
#include <GL/glew.h>
#include "Triangle.h"
#include "Rectangle.h"
#include "ShaderProgram.h"
#include "Transformation.h"
using namespace std;

/*VAO NESMI OPUSTIT MODEL*/

enum OPTION
{
	MAKE_TRIANGLE = 0,
	MAKE_RECTANGLE = 1,
	MAKE_COMPLEX = 2
};
class DrawableObject
{
private:
	GLuint VBO;
	GLuint VAO;
	Shape* shape;
	glm::mat4 matrix;
	ShaderProgram* program;
	/// <summary>
	/// Inicializuje VBO a VAO
	/// </summary>
	/// <param name="points">Pole vrcholu</param>
	/// <param name="size">Velikost pole vrcholu</param>
	/// <returns></returns>
	bool createVertexObjects(const float* points, GLsizeiptr size);
public:
	DrawableObject(OPTION o, const float* points, GLsizeiptr size, int startingPosition, int count, int Flags);
	~DrawableObject();
	bool drawShape();
	bool useVAO();
	void runTransformation(Transformation* composite);
	void setProgram(ShaderProgram* p);
};

