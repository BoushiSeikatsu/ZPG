#pragma once
#include <GL/glew.h>
#include "SOIL.H"
#include <string>
#include <vector>
using namespace std;
class Texture
{
private:
	int textureCore;
	vector<char*> textures;
public:
	Texture(int textureCore, vector<char*> textures);
	int getCore();
};

