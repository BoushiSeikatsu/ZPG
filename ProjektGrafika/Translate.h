#pragma once
#include "Transformation.h"
class Translate : public Transformation
{
private:
	glm::vec3 translationVector;
public:
	Translate(glm::vec3 translationVector);
	// Inherited via Transformation
	virtual void transform(glm::mat4* M) override;

	// Inherited via Transformation, do nothing
	virtual void changeAngle(float newAngle) override;
};

