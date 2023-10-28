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
	MATERIAL_SHININESS = 256
};

class Observer
{
private:
public:
	virtual void update(glm::mat4 newMatrix, OBSERVABLE_OBJECTS type) = 0;
	virtual void update(glm::vec3 newVector, OBSERVABLE_OBJECTS type) = 0;
	virtual void update(float newValue, OBSERVABLE_OBJECTS type) = 0;
};

