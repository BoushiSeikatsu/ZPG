#pragma once
#include "ShaderProgram.h"
#include "Translate.h"
#include "ObserverSubject.h"
//class ShaderProgram; // dopredna deklarace (z duvodu krizoveho odkazu)
class Camera : public ObserverSubject
{
	/*
	Ve chvili kdy se kamera zmeni treba stisknuti klavesy, tak by mela upozornit shader aby zmenil view a perspective matici
	*/
private:
	glm::mat4 viewMatrix;
	glm::vec3 cameraPosition;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	glm::mat4 projectionMatrix;
public:
	Camera();
	glm::mat4 getView();
	glm::vec3 getCameraPosition();
	glm::vec3 getCameraFront();
	glm::vec3 getCameraUp();
	//Apply translation on a viewMatrix using directionVector
	bool setCameraPosition(glm::vec3 directionVector);
	bool setCameraFront(glm::vec3 directionVector);
	glm::mat4 getProjection();

	// Inherited via ObserverSubject
	virtual bool addFollower(Observer* follower) override;
	virtual void notifyPropertyChanged(OBSERVABLE_OBJECTS type) override;
};

