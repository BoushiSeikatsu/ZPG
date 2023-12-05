#pragma once
#include "ShaderProgram.h"
#include "Translate.h"
#include "ObserverSubject.h"
struct CameraResolution
{
	int width;
	int height;
};
class Camera : public ObserverSubject
{
private:
	glm::mat4 viewMatrix;
	glm::vec3 cameraPosition;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	glm::mat4 projectionMatrix;
	CameraResolution cameraResolution;
public:
	Camera();
	glm::mat4 getView();
	glm::vec3 getCameraPosition();
	glm::vec3 getCameraFront();
	glm::vec3 getCameraUp();
	//Apply translation on a viewMatrix using directionVector
	bool setCameraPosition(glm::vec3 directionVector);
	bool setCameraFront(glm::vec3 directionVector);
	bool setCameraPerspective(float fovy, float aspect, float near, float far);
	glm::mat4 getProjection();
	void setResolution(int width, int height);
	CameraResolution getResolution();
	// Inherited via ObserverSubject
	virtual bool addFollower(Observer* follower) override;
	virtual void notifyPropertyChanged(OBSERVABLE_OBJECTS type) override;
};

