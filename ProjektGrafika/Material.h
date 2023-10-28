#pragma once
#include <glm/ext/vector_float3.hpp>
#include "ObserverSubject.h"
class Material : public ObserverSubject
{
private:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;
public:
	Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess);
	void changeMaterial(glm::vec3 newVector, OBSERVABLE_OBJECTS choice);
	void changeMaterial(float shininess);
	// Inherited via ObserverSubject
	virtual bool addFollower(Observer* follower) override;
	virtual void notifyPropertyChanged(OBSERVABLE_OBJECTS type) override;
};

