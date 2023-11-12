#include "Skybox.h"

Skybox::Skybox(int textureCore)
{
	this->textureCore = textureCore;
	switch (textureCore)
	{
		case 0:
		{
			glActiveTexture(GL_TEXTURE0);
			break;
		}
		case 1:
		{
			glActiveTexture(GL_TEXTURE1);
			break;
		}
	}
	GLuint textureID = SOIL_load_OGL_cubemap("Textures/xpos.jpg", "Textures/xneg.jpg", "Textures/ypos.jpg", "Textures/yneg.jpg", "Textures/zpos.jpg", "Textures/zneg.jpg", SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

bool Skybox::addFollower(Observer* follower)
{
    this->followers.push_back(follower);
    return false;
}

void Skybox::notifyPropertyChanged(OBSERVABLE_OBJECTS type)
{
    for (Observer* o : followers)
    {
        o->update(this->textureCore, SKYBOX_CHANGE);
    }
}
