#include "Lighting.h"

Lighting::Lighting(glm::vec3 lightPosition, glm::vec3 lightColor)
{
	this->lightPosition = lightPosition;
	this->lightColor = lightColor;
}

bool Lighting::addFollower(Observer* follower)
{
	followers.push_back(follower);
	int ID = follower->confirmSubjectAdded(LIGHT);
	this->idInFollower.push_back(ID);
	return true;
}

void Lighting::notifyPropertyChanged(OBSERVABLE_OBJECTS type)
{
	switch (type)
	{
		case LIGHT_POSITION:
		{
			int i = 0;
			for (Observer* observer : followers)
			{
				observer->update(this->idInFollower.at(i), this->lightPosition, type);
				i++;
			}
			break;
		}
		case LIGHT_COLOR:
		{
			int i = 0;
			for (Observer* observer : followers)
			{
				observer->update(this->idInFollower.at(i), this->lightColor, type);
				i++;
			}
			break;
		}
	}
}
