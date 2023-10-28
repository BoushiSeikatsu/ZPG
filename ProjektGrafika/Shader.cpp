#include "Shader.h"
#include <cstddef>
#include <vector>


std::string Shader::loadFile(const char* filePath)
{
	std::ifstream file(filePath);
	if (!file.is_open())
	{
		std::cout << "Unable to open file " << filePath << std::endl;
		//exit(1);
	}
	std::stringstream fileData;
	fileData << file.rdbuf();
	file.close();
	return fileData.str();
}

GLuint* Shader::createShader(long shaderType,int numberOfElements,const char* parameters)
{
	GLuint* shader = new GLuint;
	*shader = glCreateShader(shaderType);
	glShaderSource(*shader, (GLsizei)numberOfElements, &parameters, NULL);
	glCompileShader(*shader);
	//To check shader for possible errors
	GLint isCompiled = 0;
	glGetShaderiv(*shader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(*shader, maxLength, &maxLength, &errorLog[0]);

		for (int i = 0; i < maxLength; i++)
		{
			printf("%c",errorLog[i]);
		}
		// Exit with failure.
		glDeleteShader(*shader); // Don't leak the shader.
		return nullptr;
	}
	return shader;
}

GLuint* Shader::createShader(const char* filePath, long shaderType, int numberOfElements)
{
	std::string fileContent = loadFile(filePath);
	const char* parameters = fileContent.c_str();
	GLuint* shader = new GLuint;
	*shader = glCreateShader(shaderType);
	glShaderSource(*shader, (GLsizei)numberOfElements, &parameters, NULL);
	glCompileShader(*shader);
	//To check shader for possible errors
	GLint isCompiled = 0;
	glGetShaderiv(*shader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(*shader, maxLength, &maxLength, &errorLog[0]);

		for (int i = 0; i < maxLength; i++)
		{
			printf("%c", errorLog[i]);
		}
		// Exit with failure.
		glDeleteShader(*shader); // Don't leak the shader.
		return nullptr;
	}
	return shader;
}
