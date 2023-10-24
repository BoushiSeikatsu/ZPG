#pragma once
#include "Transformation.h"
#include <vector>
using namespace std;
class TransformationComposite : public Transformation
{
private:
	vector<Transformation*> transformations;
public:
	TransformationComposite() {};
	~TransformationComposite();
	void add(Transformation* t);
	// Inherited via Transformation
	virtual void transform(glm::mat4* M) override;
};

