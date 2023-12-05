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

int ShaderProgram::confirmSubjectAdded(OBSERVABLE_OBJECTS type)
{
	this->use();
	GLint lightCountLocation = glGetUniformLocation(*this->shaderProgram, "lightCount");
	glUniform1i(lightCountLocation, this->nextLightID + 1);

	disable();
	switch (type)
	{
		case CAMERA: return this->nextCameraID++; break;//Assigns ID to camera, camera version is prepared but not implemented yet
		case LIGHT: return this->nextLightID++; break;//Assigns ID to light 
		default:
			{
			printf("Wrong observable object type sent into confirmSubjectAdded!\n");
			}
	}
	//Updates the number of lights in shader
	
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
/*
There is only one flashlight and therefore LIGHT_X is referring to the flashlight 
*/
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
		case CAMERA_DIRECTION:
		{
			GLint cdVectorLocation = glGetUniformLocation(*this->shaderProgram, "cameraDirection");
			glUniform3fv(cdVectorLocation, 1, &newVector[0]);
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
			GLint lcVectorLocation = glGetUniformLocation(*this->shaderProgram, "flashlight.lightColor");
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
/*
LIGHT_CUTOFF refers to cutoff of flashlight, for lights use function with ID parameter
*/
void ShaderProgram::update(float newValue, OBSERVABLE_OBJECTS type)
{
	this->use();
	switch (type)
	{
		case MATERIAL_SHININESS:
		{
			GLint msFloatLocation = glGetUniformLocation(*this->shaderProgram, "material.shininess");
			glUniform1f(msFloatLocation, newValue);
			break;
		}
		case LIGHT_CUTOFF:
		{
			GLint lcFloatLocation = glGetUniformLocation(*this->shaderProgram, "flashlight.cutoff");
			glUniform1f(lcFloatLocation, newValue);
			break;
		}
		case LIGHT_CUTOFF_OUT:
		{
			GLint lcFloatLocation = glGetUniformLocation(*this->shaderProgram, "flashlight.outerCutoff");
			glUniform1f(lcFloatLocation, newValue);
			break;
		}
		default:
		{
			printf("Wrong type of observable object passed into shader - float part!\n");
		}
	}
	this->disable();
}
/*
Lights are in array and thus LIGHT_X is referring to specific types of lights placed somewhere in the scene
*/
void ShaderProgram::update(int elementIndex, glm::vec3 newVector, OBSERVABLE_OBJECTS type)
{
	use();
	switch (type)
	{
		case LIGHT_POSITION:
		{
			string location = string("lights[") + to_string(elementIndex) + "].position";
			GLint lpVectorLocation = glGetUniformLocation(*this->shaderProgram, location.c_str());
			glUniform3fv(lpVectorLocation, 1, &newVector[0]);
			break;
		}
		case LIGHT_COLOR:
		{
			string location = string("lights[") + to_string(elementIndex) + "].lightColor";
			GLint lcVectorLocation = glGetUniformLocation(*this->shaderProgram, location.c_str());
			glUniform3fv(lcVectorLocation, 1, &newVector[0]);
			break;
		}
		case LIGHT_DIRECTION:
		{
			string location = string("lights[") + to_string(elementIndex) + "].direction";
			GLint ldVectorLocation = glGetUniformLocation(*this->shaderProgram, location.c_str());
			glUniform3fv(ldVectorLocation, 1, &newVector[0]);
			break;
		}
	}
	disable();
}

void ShaderProgram::update(int elementIndex, float newValue, OBSERVABLE_OBJECTS type)
{
	this->use();
	switch (type)
	{
		case LIGHT_CUTOFF:
		{
			string location = string("lights[") + to_string(elementIndex) + "].cutoff";
			GLint lcFloatLocation = glGetUniformLocation(*this->shaderProgram, location.c_str());
			glUniform1f(lcFloatLocation, newValue);
			break;
		}
		default:
		{
			printf("Wrong type of observable object in update for float array values!\n");
		}
	}
	this->disable();
}
/*
We could consider merging update for bool and int values
*/
void ShaderProgram::update(bool newValue, OBSERVABLE_OBJECTS type)
{
	this->use();
	switch (type)
	{
		case FLASHLIGHT_ACTIVE:
		{
			GLint faBooleanLocation = glGetUniformLocation(*this->shaderProgram, "flashlight.activated");
			glUniform1i(faBooleanLocation, newValue);
			break;
		}
		default:
		{
			printf("Wrong observable object type passed into bool update function!\n");
		}
	}
	this->disable();
}

void ShaderProgram::update(int newValue, const char* varName, OBSERVABLE_OBJECTS type)
{
	this->use();
	switch (type)
	{
		case TEXTURE_CHANGE:
		{
			GLint txBooleanLocation = glGetUniformLocation(*this->shaderProgram, varName);
			glUniform1i(txBooleanLocation, newValue);
			break;
		}
	}
	this->disable();
}

bool ShaderProgram::linkTransformation(const char* matrixName, glm::mat4 matrix)
{
	GLint matrixLocation = glGetUniformLocation(*this->shaderProgram, matrixName);
	glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, &matrix[0][0]);
	return true;
}

bool ShaderProgram::setObjectColor(glm::vec3 objectColor)
{
	GLint objectColorLocation = glGetUniformLocation(*this->shaderProgram, "objectColor");
	glUniform3fv(objectColorLocation, 1, &objectColor[0]);
	return true;
}
