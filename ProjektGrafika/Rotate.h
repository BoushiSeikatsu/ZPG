#pragma once
#include "Transformation.h"
class Rotate : public Transformation
{
private:
	float angle;
	glm::vec3 rotationAxis;
public:
	Rotate(float angle, glm::vec3 rotationAxis);
	// Inherited via Transformation
	virtual void transform(glm::mat4* M) override;

	// Inherited via Transformation, add new angle into old angle
	virtual void changeAngle(float newAngle) override;
};

