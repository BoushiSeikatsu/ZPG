#include "Translate.h"

Translate::Translate(glm::vec3 translationVector)
{
    this->translationVector = translationVector;
}

void Translate::transform(glm::mat4* M)
{
    *M = glm::translate(*M, translationVector);
}

void Translate::changeAngle(float newAngle)
{
}
