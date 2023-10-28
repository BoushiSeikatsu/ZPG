#include "ShaderProgram.h"
//#include "Camera.h"

ShaderProgram::~ShaderProgram()
{
	for (auto shader : listBasicShaders)
	{
		delete shader;
		shader = nullptr;
	}
	listBasicShaders.clear();
	delete shaderProgram;
	shaderProgram = nullptr;
}

bool ShaderProgram::add(long shaderType, int numberOfElements,const char* parameters)
{
    listBasicShaders.push_back(Shader::createShader(shaderType, numberOfElements, parameters));
	return true;
}

bool ShaderProgram::add(const char* filePath, long shaderType, int numberOfElements)
{
	listBasicShaders.push_back(Shader::createShader(filePath, shaderType, numberOfElements));
	return true;
}

bool ShaderProgram::use()
{
	glUseProgram(*shaderProgram);
	return true;
}

bool ShaderProgram::disable()
{
	glUseProgram(0);
	return true;
}


bool ShaderProgram::assembleProgram()
{
	GLuint* program = new GLuint;
	*program = glCreateProgram();
	for (auto shader : listBasicShaders)
	{
		glAttachShader(*program, *shader);
	}
	glLinkProgram(*program);
	this->shaderProgram = program;
	return true;
}

void ShaderProgram::update(glm::mat4 newMatrix, OBSERVABLE_OBJECTS type)
{
	use();
	switch (type)
	{
		case CAMERA_VIEW:
		{
			GLint vMatrixLocation = glGetUniformLocation(*this->shaderProgram, "viewMatrix");
			glUniformMatrix4fv(vMatrixLocation, 1, GL_FALSE, &newMatrix[0][0]);
			break;
		}
		case CAMERA_PERSPECTIVE:
		{
			GLint pMatrixLocation = glGetUniformLocation(*this->shaderProgram, "projectionMatrix");
			glUniformMatrix4fv(pMatrixLocation, 1, GL_FALSE, &newMatrix[0][0]);
			break;
		}
		default:
		{
			printf("Wrong type of observable object passed into shader - matrix part!\n");
		}
	}
	disable();
}

void ShaderProgram::update(glm::vec3 newVector, OBSERVABLE_OBJECTS type)
{
	use();
	switch (type)
	{
		case CAMERA_POSITION:
		{
			GLint cPVectorLocation = glGetUniformLocation(*this->shaderProgram, "cameraPosition");
			glUniform3fv(cPVectorLocation, 1, &newVector[0]);
			break;
		}
		case LIGHT_POSITION:
		{
			GLint lpVectorLocation = glGetUniformLocation(*this->shaderProgram, "lightPosition");
			glUniform3fv(lpVectorLocation, 1, &newVector[0]);
			break;
		}
		case LIGHT_COLOR:
		{
			GLint lcVectorLocation = glGetUniformLocation(*this->shaderProgram, "lightColor");
			glUniform3fv(lcVectorLocation, 1, &newVector[0]);
			break;
		}
		case MATERIAL_AMBIENT:
		{
			GLint maVectorLocation = glGetUniformLocation(*this->shaderProgram, "material.ambient");
			glUniform3fv(maVectorLocation, 1, &newVector[0]);
			break;
		}
		case MATERIAL_DIFFUSE:
		{
			GLint mdVectorLocation = glGetUniformLocation(*this->shaderProgram, "material.diffuse");
			glUniform3fv(mdVectorLocation, 1, &newVector[0]);
			break;
		}
		case MATERIAL_SPECULAR:
		{
			GLint mcVectorLocation = glGetUniformLocation(*this->shaderProgram, "material.specular");
			glUniform3fv(mcVectorLocation, 1, &newVector[0]);
			break;
		}
		default:
		{
			printf("Wrong type of observable object passed into shader - vector part!\n");
			break;
		}
			
	}
	disable();
}

void ShaderProgram::update(float newValue, OBSERVABLE_OBJECTS type)
{
	switch (type)
	{
		case MATERIAL_SHININESS:
		{
			GLint msFloatLocation = glGetUniformLocation(*this->shaderProgram, "material.shininess");
			glUniform1f(msFloatLocation, newValue);
			break;
		}
		default:
		{
			printf("Wrong type of observable object passed into shader - float part!\n");
		}
	}
}

bool ShaderProgram::linkTransformation(const char* matrixName, glm::mat4 matrix)
{
	GLint matrixLocation = glGetUniformLocation(*this->shaderProgram, matrixName);
	glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, &matrix[0][0]);
	return true;
}
