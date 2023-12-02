#pragma once
#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h>
//Include GLM  

#include <glm/vec3.hpp> // glm::vec3

#include <glm/vec4.hpp> // glm::vec4

#include <glm/mat4x4.hpp> // glm::mat4

#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
//Flags pro urceni jestli mame v poli hodnoty vrcholu, barev a textur, kdyby byly vsechny tri pak VERTICES | COLOR | TEXTURE
enum ATTRIBUTES
{
	VERTICES = 1,
	COLOR = 2,
	TEXTURE = 4,
	MODEL = 8
};

class Shape
{
protected:
	GLint startingPosition;
	GLsizei count;
	virtual bool setupVertexObjects(GLuint* VBO, GLuint* VAO) = 0;
public:
	Shape(int startingPosition, int count);
	virtual bool createShape() = 0;
	virtual bool deleteShape() = 0;
	virtual bool updateShape() = 0;
};
