#pragma once
#include <glm/ext/matrix_float4x4.hpp>

enum OBSERVABLE_OBJECTS
{
	CAMERA_VIEW = 1,
	CAMERA_PERSPECTIVE = 2,
	LIGHT_POSITION = 4,
	LIGHT_COLOR = 8,
	CAMERA_POSITION = 16,
	MATERIAL_AMBIENT = 32,
	MATERIAL_DIFFUSE = 64,
	MATERIAL_SPECULAR = 128,
	MATERIAL_SHININESS = 256,
	CAMERA = 512,
	LIGHT = 1024,
	LIGHT_CUTOFF = 2048,
	LIGHT_DIRECTION = 4096,
	FLASHLIGHT_ACTIVE = 8192,
	CAMERA_DIRECTION = 16384,
	TEXTURE_CHANGE = 32768,
	SKYBOX_CHANGE = 65536
};

class Observer
{
private:
public:
	virtual int confirmSubjectAdded(OBSERVABLE_OBJECTS type) = 0;
	virtual void update(bool newValue, OBSERVABLE_OBJECTS type) = 0;
	virtual void update(glm::mat4 newMatrix, OBSERVABLE_OBJECTS type) = 0;
	virtual void update(glm::vec3 newVector, OBSERVABLE_OBJECTS type) = 0;
	virtual void update(float newValue, OBSERVABLE_OBJECTS type) = 0;
	virtual void update(int newValue, const char* varName, OBSERVABLE_OBJECTS type) = 0;
	virtual void update(int elementIndex, glm::vec3 newVector, OBSERVABLE_OBJECTS type) = 0;
	virtual void update(int elementIndex, float newValue, OBSERVABLE_OBJECTS type) = 0;
};

