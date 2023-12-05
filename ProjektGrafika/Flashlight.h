#pragma once
#include "ObserverSubject.h"
class Flashlight : public ObserverSubject
{
private:
	glm::vec3 lightColor;
	float cutoff;
	float outerCutoff;
	bool active = false;
public:
	Flashlight(glm::vec3 lightColor, float cutoff, float outerCutoff);
	void use();
	bool state();
	void disable();
	// Inherited via ObserverSubject
	virtual bool addFollower(Observer* follower) override;
	virtual void notifyPropertyChanged(OBSERVABLE_OBJECTS type) override;
};

