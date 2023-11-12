#pragma once
#include <map>
#include "DrawableObject.h"
#include "TransformationComposite.h"
#include "Lighting.h"
#include <string>
#include "Camera.h"
class JsonAssistant
{
private:
public:
	static void saveScene(string fileName, map<int, DrawableObject*> listOfModels, map<int, ShaderProgram*> listOfShaderPrograms, map<int, TransformationComposite*> listOfTransformations, map<int, Lighting*> listOfLights, Camera* camera);
	static void loadScene(string fileName, map<int, DrawableObject*> &listOfModels, map<int, ShaderProgram*> &listOfShaderPrograms, map<int, TransformationComposite*> &listOfTransformations, map<int, Lighting*> &listOfLights, Camera* camera);
};

