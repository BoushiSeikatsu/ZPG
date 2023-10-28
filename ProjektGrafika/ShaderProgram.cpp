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

void ShaderProgram::update(glm::mat4 newMatrix, OBSERVABLE_OBJECTS choice)
{
	use();
	switch (choice)
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
			printf("Wrong observable object passed into shader!\n");
		}
	}
	disable();
}

void ShaderProgram::update(glm::vec3 newVector, OBSERVABLE_OBJECTS choice)
{
	use();
	switch (choice)
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
		
		default:
		{
			printf("Wrong observable object passed into shader!\n");
			break;
		}
			
	}
	disable();
}

bool ShaderProgram::linkTransformation(const char* matrixName, glm::mat4 matrix)
{
	GLint matrixLocation = glGetUniformLocation(*this->shaderProgram, matrixName);
	glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, &matrix[0][0]);
	return true;
}
