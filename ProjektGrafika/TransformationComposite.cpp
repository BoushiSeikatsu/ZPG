#include "TransformationComposite.h"

TransformationComposite::~TransformationComposite()
{
    for (auto transformation : this->transformations)
    {
        delete transformation;
        transformation = nullptr;
    }
    delete this;
}

void TransformationComposite::add(Transformation* t)
{
    transformations.push_back(t);
}

void TransformationComposite::transform(glm::mat4* M)
{
    for (auto& transformation : transformations)
    {
        transformation->transform(M);
    }
}

void TransformationComposite::changeAngle(float newAngle)
{
    for(Transformation* t : transformations)
    {
        t->changeAngle(newAngle);
    }
}
