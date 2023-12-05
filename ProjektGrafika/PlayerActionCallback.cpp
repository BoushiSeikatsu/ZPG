#include "PlayerActionCallback.h"

int PlayerActionCallback::indexSelectedModel = 0;
glm::vec3 PlayerActionCallback::positionSelectedModel;
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

void PlayerActionCallback::onMouseClicked(GLFWwindow* window, float xCursor, float yCursor)
{
	GLbyte color[4];
	GLfloat depth;
	GLuint index;
	Camera* camera = (Camera*)glfwGetWindowUserPointer(window);
	GLint x = xCursor;
	GLint y = yCursor;

	int newy = camera->getResolution().height - y;

	glReadPixels(x, newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
	glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
	glReadPixels(x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

	printf("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth %f, stencil index % u\n", x, y, color[0], color[1], color[2], color[3], depth, index);

		//Můžeme nastavit vybrané těleso scena->setSelect(index-1);

		//Můžeme vypočíst pozici v globálním souřadném systému.  
		glm::vec3 screenX = glm::vec3(x, newy, depth);
	glm::mat4 view = camera->getView();
	glm::mat4 projection = camera->getProjection();
	glm::vec4 viewPort = glm::vec4(0, 0, camera->getResolution().width, camera->getResolution().height);
	glm::vec3 pos = glm::unProject(screenX, view, projection, viewPort);

	printf("unProject [%f,%f,%f]\n", pos.x, pos.y, pos.z);
	indexSelectedModel = index;
	positionSelectedModel = pos;
}
