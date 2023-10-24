#include "Rotate.h"

Rotate::Rotate(float angle, glm::vec3 rotationAxis)
{
    this->angle = angle;
    this->rotationAxis = rotationAxis;
}

void Rotate::transform(glm::mat4* M)
{
    *M = glm::rotate(*M, angle, rotationAxis);
}
