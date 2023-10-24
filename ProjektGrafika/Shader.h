#pragma once
#include <GL/glew.h>
class Shader
{
public:
	static GLuint* createShader(long shaderType, int numberOfElements,const char* parameters);
};

