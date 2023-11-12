#pragma once
#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h>
//Include GLM  

#include <glm/vec3.hpp> // glm::vec3

#include <glm/vec4.hpp> // glm::vec4

#include <glm/mat4x4.hpp> // glm::mat4

#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

//Include the standard C++ headers  

#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <map>
#include "CameraCallback.h"
#include "SceneCallback.h"
#include "DrawableObject.h"
#include "ShaderProgram.h"
#include "Transformation.h"
#include "TransformationComposite.h"
#include "Rotate.h"
#include "Translate.h"
#include "Scale.h"
#include "Camera.h"
#include "Lighting.h"
#include "Flashlight.h"
#include "Skybox.h"


class Application
{
private:
	GLFWwindow* window;
	int major, minor, revision, width, height;
	/*
	Ve chvili kdy budeme pouzivat vice shaderu a rozdelime je mezi modely tak by to chtelo prekopat na vice listu at kazdy shape list ma vlastni shader
	do listu by se dal pridat atribut indexShader ktery by v sobe mel pozici shaderu v listOfShaders
	*/
	map<int, DrawableObject*> listOfModels;
	map<int,ShaderProgram*> listOfShaderPrograms;
	map<int, TransformationComposite*> listOfTransformations;
	map<int, Lighting*> listOfLights;
	Camera* camera;
	Flashlight* flashlight;
	std::vector<void*> windowPointers;
public:
	Application();
	~Application();
	bool initialize();
	bool createShaders();
	bool createModels();
	bool createTransformation();
	bool createLighting();
	void run();
};

