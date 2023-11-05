#include "Flashlight.h"

Flashlight::Flashlight(glm::vec3 lightColor, float cutoff)
{
    this->lightColor = lightColor;
    this->cutoff = cutoff;
}

void Flashlight::use()
{
    active = true;
    notifyPropertyChanged(FLASHLIGHT_ACTIVE);
}

bool Flashlight::state()
{
    return this->active;
}

void Flashlight::disable()
{
    active = false;
    notifyPropertyChanged(FLASHLIGHT_ACTIVE);
}

bool Flashlight::addFollower(Observer* follower)
{
    followers.push_back(follower);
    return true;
}

void Flashlight::notifyPropertyChanged(OBSERVABLE_OBJECTS type)
{
    switch (type)
    {
        case LIGHT_COLOR:
        {
            for (Observer* observer : followers)
            {
                observer->update(this->lightColor, type);
            }
            break;
        }
        case LIGHT_CUTOFF:
        {
            for (Observer* observer : followers)
            {
                observer->update(this->cutoff, type);
            }
            break;
        }
        case FLASHLIGHT_ACTIVE:
        {
            for (Observer* observer : followers)
            {
                observer->update(this->active, type);
            }
            break;
        }
    }
}
