#pragma once
#include "Shape.h"
#include <vector>
#include <GL/glew.h>
#include "Triangle.h"
#include "Rectangle.h"
#include "ShaderProgram.h"
#include "Transformation.h"
#include "Material.h"
#include<assimp/Importer.hpp>// C++ importerinterface
#include<assimp/scene.h>// aiSceneoutputdata structure
#include<assimp/postprocess.h>// Post processingflags
using namespace std;
using namespace glm;
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
	Material* material;
	glm::vec3 objectColor;
	/// <summary>
	/// Inicializuje VBO a VAO
	/// </summary>
	/// <param name="points">Pole vrcholu</param>
	/// <param name="size">Velikost pole vrcholu</param>
	/// <returns></returns>
	bool createVertexObjects(const float* points, GLsizeiptr size);
	vector<float> loadModel(const char* fileName, int& count);
public:
	DrawableObject(OPTION o, const float* points, GLsizeiptr size, int startingPosition, int count, int Flags, glm::vec3 objectColor = glm::vec3(0.385, 0.647, 0.812));
	DrawableObject(const char* modelName, int Flags);
	~DrawableObject();
	bool drawShape();
	bool useVAO();
	void runTransformation(Transformation* composite);
	void setProgram(ShaderProgram* p);
	void setMaterial(Material* m);
	void setMaterial(Material* m, Texture* t);
};
