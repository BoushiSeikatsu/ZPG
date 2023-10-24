#pragma once
#include "ObserverSubject.h"
class Lighting : public ObserverSubject
{
private:
	glm::vec3 lightPosition;
	glm::vec3 lightColor;
public:
	Lighting(glm::vec3 lightPosition, glm::vec3 lightColor);
	// Inherited via ObserverSubject
	virtual bool addFollower(Observer* follower) override;

	virtual void notifyPropertyChanged(OBSERVABLE_OBJECTS type) override;

};

