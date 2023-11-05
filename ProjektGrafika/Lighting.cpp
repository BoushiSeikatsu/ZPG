#include "Lighting.h"

Lighting::Lighting(glm::vec3 lightPosition, glm::vec3 lightColor, bool isDirectional)
{
	if (isDirectional)
	{
		this->lightPosition = glm::vec3(-1, -1, -1);
		this->lightColor = lightColor;
		this->cutoff = -1;
		this->direction = lightPosition;//Its actually direction 
	}
	else
	{
		this->lightPosition = lightPosition;
		this->lightColor = lightColor;
		this->cutoff = -1;
		this->direction = glm::vec3(-1, -1, -1);
	}
	
}

Lighting::Lighting(glm::vec3 lightPosition, glm::vec3 lightColor, glm::vec3 direction, float cutoff)
{
	this->lightPosition = lightPosition;
	this->lightColor = lightColor;
	this->cutoff = cutoff;
	this->direction = direction;
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
		case LIGHT_DIRECTION:
		{
			int i = 0;
			for (Observer* observer : followers)
			{
				observer->update(this->idInFollower.at(i), this->direction, type);
				i++;
			}
			break;
		}
		case LIGHT_CUTOFF:
		{
			int i = 0;
			for (Observer* observer : followers)
			{
				observer->update(this->idInFollower.at(i), this->cutoff, type);
				i++;
			}
			break;
		}
	}
}
