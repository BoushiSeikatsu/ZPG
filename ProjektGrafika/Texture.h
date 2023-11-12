#pragma once
#include <GL/glew.h>
#include <SOIL.h>
#include <string>
#include <vector>
using namespace std;
class Texture
{
private:
	int textureCore;
	//vector<const char*> textures;
	const char* textureLocation;
public:
	Texture(int textureCore, const char* textureLocation);
	int getCore();
};

