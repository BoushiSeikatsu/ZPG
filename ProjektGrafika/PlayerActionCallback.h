#pragma once
#include "Camera.h"
#include <GLFW/glfw3.h>
#include "Flashlight.h"
class PlayerActionCallback
{
private:
	static bool keyPressed;
public:
	static void onKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void onMouseClicked(GLFWwindow* window, float xCursor, float yCursor);
};

