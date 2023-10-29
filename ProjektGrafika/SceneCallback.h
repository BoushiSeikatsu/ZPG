#pragma once
#include <GLFW/glfw3.h>
class SceneCallback
{
private:
	static int sceneIndex;
	static int sceneLimit;
public:
	static void onKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void setSceneLimit(int limit);
	static int getSceneIndex();
};