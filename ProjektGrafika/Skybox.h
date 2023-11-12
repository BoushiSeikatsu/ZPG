#pragma once
#include <GL/glew.h>
#include <SOIL.h>
#include "ObserverSubject.h"
class Skybox : public ObserverSubject
{
private:
	int textureCore;
public:
	Skybox(int textureCore);
	// Inherited via ObserverSubject
	virtual bool addFollower(Observer* follower) override;

	virtual void notifyPropertyChanged(OBSERVABLE_OBJECTS type) override;

};

