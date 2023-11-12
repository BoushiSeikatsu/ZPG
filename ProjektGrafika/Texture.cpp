#include "Texture.h"

Texture::Texture(int textureCore, const char* textureLocation)
{
	this->textureCore = textureCore;
	switch (textureCore)
	{
		case 0:
		{
			glActiveTexture(GL_TEXTURE0);
			break;
		}
	}
	//If texture is meant for skycube or not
	if (strcmp(textureLocation, "Skycube") == 0)
	{
		GLuint textureID = SOIL_load_OGL_cubemap("Textures/xpos.jpg","Textures/xneg.jpg","Textures/ypos.jpg","Textures/yneg.jpg","Textures/zpos.jpg","Textures/zneg.jpg",SOIL_LOAD_RGB,SOIL_CREATE_NEW_ID,SOIL_FLAG_MIPMAPS    );
		glBindTexture(GL_TEXTURE_2D, textureID);
	}
	else
	{
		GLuint textureID = SOIL_load_OGL_texture(textureLocation, SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
		glBindTexture(GL_TEXTURE_2D, textureID);
	}
	
	this->textureLocation = textureLocation;
}

int Texture::getCore()
{
	return this->textureCore;
}
