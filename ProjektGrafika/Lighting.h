#pragma once
#include "ObserverSubject.h"

class Lighting : public ObserverSubject
{
private:
	glm::vec3 lightPosition;
	glm::vec3 lightColor;
	float cutoff;
	glm::vec3 direction;
	std::vector<int> idInFollower;//Id on index one is ID of light for follower on index one in followers vector
public:
	Lighting(glm::vec3 lightPosition, glm::vec3 lightColor, bool isDirectional);
	Lighting(glm::vec3 lightPosition, glm::vec3 lightColor, glm::vec3 direction, float cutoff);
	// Inherited via ObserverSubject
	virtual bool addFollower(Observer* follower) override;

	virtual void notifyPropertyChanged(OBSERVABLE_OBJECTS type) override;

};

