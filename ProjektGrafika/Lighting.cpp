#include "Lighting.h"

Lighting::Lighting(glm::vec3 lightPosition, glm::vec3 lightColor)
{
	this->lightPosition = lightPosition;
	this->lightColor = lightColor;
}

bool Lighting::addFollower(Observer* follower)
{
	followers.push_back(follower);
	return true;
}

void Lighting::notifyPropertyChanged(OBSERVABLE_OBJECTS type)
{
	switch (type)
	{
		case LIGHT_POSITION:
		{
			for (Observer* observer : followers)
			{
				observer->update(this->lightPosition, type);
			}
			break;
		}
		case LIGHT_COLOR:
		{
			for (Observer* observer : followers)
			{
				observer->update(this->lightColor, type);
			}
			break;
		}
	}
}
