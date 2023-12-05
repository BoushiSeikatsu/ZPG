#include "Camera.h"
//カメラはスフィアを見てて、スフィアは振り返っている
Camera::Camera()
{
	this->cameraPosition = glm::vec3(0.0f, 1.0f, 15.0f);
	this->cameraFront = glm::vec3(0.001f, 0.0f, -1.0f);//If x = 0 then first frame doesnt draw objects because matrix has nan values -> its because of our up value set to (0,1,0)
	this->cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	this->viewMatrix = glm::lookAt(this->cameraPosition, this->cameraPosition + this->cameraFront, this->cameraUp);
	this->projectionMatrix = glm::perspective(glm::radians(60.0f), 4.0f / 3.0f, 0.1f, 100.0f);
}

glm::mat4 Camera::getView()
{
	return this->viewMatrix;
}

glm::vec3 Camera::getCameraPosition()
{
	return this->cameraPosition;
}

glm::vec3 Camera::getCameraFront()
{
	return this->cameraFront;
}

glm::vec3 Camera::getCameraUp()
{
	return this->cameraUp;
}

bool Camera::setCameraPosition(glm::vec3 cameraPosVector)
{
	this->cameraPosition = cameraPosVector;
	viewMatrix = glm::lookAt(this->cameraPosition, this->cameraPosition + this->cameraFront, this->cameraUp);
	//Notify shader that both camera position and camera's view changed, camera position is important for light reflection and view is for setting camera view
	notifyPropertyChanged(CAMERA_POSITION);
	notifyPropertyChanged(CAMERA_VIEW);
	return true;
}

bool Camera::setCameraFront(glm::vec3 cameraFrontVector)
{
	this->cameraFront = cameraFrontVector;
	viewMatrix = glm::lookAt(this->cameraPosition, this->cameraPosition + this->cameraFront, this->cameraUp);
	notifyPropertyChanged(CAMERA_DIRECTION);
	notifyPropertyChanged(CAMERA_VIEW);
	return true;
}

bool Camera::setCameraPerspective(float fovy, float aspect, float near, float far)
{
	this->projectionMatrix = glm::perspective(glm::radians(fovy), aspect, near, far);
	notifyPropertyChanged(CAMERA_PERSPECTIVE);
	return true;
}

glm::mat4 Camera::getProjection()
{
	return this->projectionMatrix;
}

void Camera::setResolution(int width, int height)
{
	this->cameraResolution.width = width;
	this->cameraResolution.height = height;
}

CameraResolution Camera::getResolution()
{
	return this->cameraResolution;
}

bool Camera::addFollower(Observer* follower)
{
	followers.push_back(follower);
	return true;
}

void Camera::notifyPropertyChanged(OBSERVABLE_OBJECTS type)
{
	switch (type)
	{
		case CAMERA_VIEW:
		{
			for (Observer* observer : followers)
			{
				observer->update(this->viewMatrix, type);
			}
			break;
		}
		//Ready in case we would like to implement zoom in our application
		//For now its used only in initialization process when we setup perspective for the first time
		case CAMERA_PERSPECTIVE:
		{
			for (Observer* observer : followers)
			{
				observer->update(this->projectionMatrix, type);
			}
			break;
		}
		case CAMERA_POSITION:
		{
			for (Observer* observer : followers)
			{
				observer->update(this->cameraPosition, type);
			}
			break;
		}
		case CAMERA_DIRECTION:
		{
			for (Observer* observer : followers)
			{
				observer->update(this->cameraFront, type);
			}
			break;
		}
		default:
		{
			printf("Wrong observable object type passed into camera notify - %d\n",type);
			break;
		}
	}
}
