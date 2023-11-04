#include "Scale.h"

Scale::Scale(glm::vec3 scalingVector)
{
    this->scalingVector = scalingVector;
}

void Scale::transform(glm::mat4* M)
{
    *M = glm::scale(*M, scalingVector);
}

void Scale::changeAngle(float newAngle)
{

}
