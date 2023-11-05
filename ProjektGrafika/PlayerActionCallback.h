#pragma once
#include <GLFW/glfw3.h>
#include "Flashlight.h"
class PlayerActionCallback
{
private:
	static bool keyPressed;
public:
	static void onKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods);
};

