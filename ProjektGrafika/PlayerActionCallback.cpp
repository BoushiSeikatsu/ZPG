#include "PlayerActionCallback.h"

void PlayerActionCallback::onKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	switch (key)
	{
		case 'F':
		{
			//TODO
			/*Flashlight* flashlight = (Flashlight*)glfwGetWindowUserPointer(window);
			if (flashlight->state())
			{
				flashlight->disable();
			}
			else
			{
				flashlight->use();
			}*/
			break;
		}
	}
}
