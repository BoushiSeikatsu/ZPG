#pragma once
#include "Camera.h"
#include <GLFW/glfw3.h>
#include "Flashlight.h"
class PlayerActionCallback
{
private:
	static bool keyPressed;
public:
	static int indexSelectedModel;
	static glm::vec3 positionSelectedModel;
	static void onKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void onMouseClicked(GLFWwindow* window, float xCursor, float yCursor);
};

