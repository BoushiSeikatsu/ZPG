#pragma once
#include "Observer.h"
#include <vector>
class ObserverSubject
{
protected:
	std::vector<Observer*> followers;
public:
	virtual bool addFollower(Observer* follower) = 0;
	virtual void notifyPropertyChanged(OBSERVABLE_OBJECTS type) = 0;
};

