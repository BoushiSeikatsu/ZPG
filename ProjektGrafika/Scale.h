#pragma once
#include "Transformation.h"
class Scale : public Transformation
{
private:
	glm::vec3 scalingVector;
public:
	Scale(glm::vec3 scalingVector);
	// Inherited via Transformation
	virtual void transform(glm::mat4* M) override;
};

