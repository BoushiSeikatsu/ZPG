#include "Material.h"

Material::Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess)
{
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->shininess = shininess;
}

void Material::changeMaterial(glm::vec3 newVector,OBSERVABLE_OBJECTS type)
{
	switch (type)
	{
		case MATERIAL_AMBIENT:
		{
			this->ambient = newVector;
			notifyPropertyChanged(type);
			break;
		}
		case MATERIAL_DIFFUSE:
		{
			this->diffuse = newVector;
			notifyPropertyChanged(type);
			break;
		}
		case MATERIAL_SPECULAR:
		{
			this->specular = newVector;
			notifyPropertyChanged(type);
			break;
		}
		default:
		{
			printf("Wrong observable object type passed into material change\n");
		}
	}
	
}

void Material::changeMaterial(float shininess)
{
	this->shininess = shininess;
	notifyPropertyChanged(MATERIAL_SHININESS);
}

bool Material::addFollower(Observer* follower)
{
	followers.push_back(follower);
	return true;
}

void Material::notifyPropertyChanged(OBSERVABLE_OBJECTS type)
{
	switch (type)
	{
		case MATERIAL_AMBIENT:
		{
			for (Observer* observer : followers)
			{
				observer->update(this->ambient, type);
			}
			break;
		}
		case MATERIAL_DIFFUSE:
		{
			for (Observer* observer : followers)
			{
				observer->update(this->diffuse, type);
			}
			break;
		}
		case MATERIAL_SPECULAR:
		{
			for (Observer* observer : followers)
			{
				observer->update(this->specular, type);
			}
			break;
		}
		case MATERIAL_SHININESS:
		{
			for (Observer* observer : followers)
			{
				observer->update(this->shininess, type);
			}
			break;
		}
		default:
		{
			printf("Wrong observable object type passed into material!\n");
		}
	}
}
