#include "Texture.h"

Texture::Texture(int textureCore, vector<char*> textures)
{
	switch (textureCore)
	{
		case 0:
		{
			glActiveTexture(GL_TEXTURE0);
			break;
		}
	}
	//GLuint textureID = SOIL_load_OGL_texture(textures.at(0), SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	this->textures = textures;
}

int Texture::getCore()
{
	return this->textureCore;
}
