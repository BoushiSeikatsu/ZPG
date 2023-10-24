#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Camera.h"
class CameraCallback : public Camera
{
private:
	static bool firstMouse;
	static float yaw;
	static float pitch;
	static float lastX;
	static float lastY;
public:
	
	static void onMouseMoved(GLFWwindow* window, double xpos, double ypos);
	static void onKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods);
};

