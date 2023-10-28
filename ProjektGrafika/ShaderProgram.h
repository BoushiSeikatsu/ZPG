#pragma once
#include <vector>
#include <map>
#include "Shader.h"
#include "Observer.h"
#include "Transformation.h"
using namespace std;
/*
Shader by mel mit id a nemel by mit get metodu, NESMI TAM BYT GET NIKDO HO NEMUZE ZISKAT
Navic mi budeme potrebovat jenom shaderProgram teoreticky, shadery jednotne nepotrebujem 
Shader program by mel mit metodu use ve ktere zavola useProgram 
*/
//class Camera; // dopredna deklarace (z duvodu krizoveho odkazu)
class ShaderProgram : public Observer
{
private:
	vector<GLuint*> listBasicShaders;
	GLuint* shaderProgram;//shader_id
public:
	~ShaderProgram();
	bool add(long shaderType, int numberOfElements,const char* parameters);
	bool add(const char* filePath, long shaderType, int numberOfElements);
	bool use();
	bool disable();
	bool linkTransformation(const char* matrixName, glm::mat4 matrix);
	bool assembleProgram();
	// Inherited via Observer
	virtual void update(glm::mat4 newMatrix, OBSERVABLE_OBJECTS type) override;

	// Inherited via Observer
	virtual void update(glm::vec3 newVector, OBSERVABLE_OBJECTS type) override;

	// Inherited via Observer
	virtual void update(float newValue, OBSERVABLE_OBJECTS type) override;
};

