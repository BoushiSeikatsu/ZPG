#pragma once
#include <GL/glew.h>
#include <string.h> 
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <sstream>
class Shader
{
private:
	static std::string loadFile(const char* filePath);
public:
	static GLuint* createShader(long shaderType, int numberOfElements,const char* parameters);
	static GLuint* createShader(const char* filePath, long shaderType, int numberOfElements);
};

