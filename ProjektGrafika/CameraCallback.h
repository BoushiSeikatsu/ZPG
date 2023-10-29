#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Camera.h"
#include "SceneCallback.h"
class CameraCallback : public Camera
{
private:
	static bool firstMouse;
	static float yaw;
	static float pitch;
	static float lastX;
	static float lastY;
	static bool rightClickPressed;
public:
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void onMouseMoved(GLFWwindow* window, double xpos, double ypos);
	static void onKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
};

