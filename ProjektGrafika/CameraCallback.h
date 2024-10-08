#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Camera.h"
#include "SceneCallback.h"
#include "PlayerActionCallback.h"
class CameraCallback : public Camera
{
private:
	static bool firstMouse;
	static float cameraSpeed;
	static float yaw;
	static float pitch;
	static float lastX;
	static float lastY;
	static float currentX;
	static float currentY;
	static bool rightClickPressed;
	static bool leftClickPressed;
	static bool leftShiftPressed;
public:
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void onMouseMoved(GLFWwindow* window, double xpos, double ypos);
	static void onKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
};

