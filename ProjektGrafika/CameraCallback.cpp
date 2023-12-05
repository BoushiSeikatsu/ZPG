#include "CameraCallback.h"
//Initialize CameraCallback variables
//ZPGのせいに、死にたい。誰か助けてくれよ
bool CameraCallback::firstMouse = true;
float CameraCallback::cameraSpeed = 0.05f;
float CameraCallback::yaw = -90.0;
float CameraCallback::pitch = 0;
float CameraCallback::lastX = 400;
float CameraCallback::lastY = 300;
float CameraCallback::currentX = lastX;
float CameraCallback::currentY = lastY;
bool CameraCallback::rightClickPressed = false;
bool CameraCallback::leftClickPressed = false;
bool CameraCallback::leftShiftPressed = false;
void CameraCallback::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        rightClickPressed = true;
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
        rightClickPressed = false;
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (!leftClickPressed)
        {
            PlayerActionCallback::onMouseClicked(window, currentX, currentY);
            leftClickPressed = true;
        }
        if (action == GLFW_RELEASE)
        {
            leftClickPressed = false;
        }
    }
}

void CameraCallback::onMouseMoved(GLFWwindow* window, double xpos, double ypos)
{
    if (rightClickPressed)
    {
        if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }
        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos;
        lastX = xpos;
        lastY = ypos;
        float sensitivity = 0.1f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;
        yaw += xoffset;
        pitch += yoffset;
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
        /* if (yaw > 0.f)
             yaw = 0.f;
         if (yaw < -179.0f)
             yaw = -179.0f;*/
        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        glm::vec3 cameraFront = glm::normalize(direction);
        Camera* camera = (Camera*)glfwGetWindowUserPointer(window);
        camera->setCameraFront(direction);
    }
    else
    {
        firstMouse = true;
    }
    currentX = xpos;
    currentY = ypos;
}

void CameraCallback::onKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Camera* camera = (Camera*)glfwGetWindowUserPointer(window);
    glm::vec3 outputVector;
    switch (key)
    {
    //case 'GLFW_ESCAPE_KEY': 
        case 'W':  outputVector = camera->getCameraPosition() + (cameraSpeed * camera->getCameraFront()); camera->setCameraPosition(outputVector); break;
        case 'S': outputVector = camera->getCameraPosition() - (cameraSpeed * camera->getCameraFront()); camera->setCameraPosition(outputVector); break;
        case 'A': 
        {
            outputVector = camera->getCameraPosition() - (glm::normalize(glm::cross(camera->getCameraFront(), camera->getCameraUp())) * cameraSpeed);
            camera->setCameraPosition(outputVector);
            break;
        } 
        case 'D':
        {
            outputVector = camera->getCameraPosition() + (glm::normalize(glm::cross(camera->getCameraFront(), camera->getCameraUp())) * cameraSpeed);
            camera->setCameraPosition(outputVector);
            break;
        }
        case 'F':
        {
            PlayerActionCallback::onKeyPressed(window, key, scancode, action, mods);
            break;
        }
        case GLFW_KEY_RIGHT:
        {
            //We should make main Callback class and that will distribute the calls to other Callback classes
            SceneCallback::onKeyPressed(window, key, scancode, action, mods);
            break;
        }
        case GLFW_KEY_LEFT:
        {
            SceneCallback::onKeyPressed(window, key, scancode, action, mods);
            break;
        }
        case GLFW_KEY_LEFT_SHIFT:
        {
            if (!leftShiftPressed)
            {
                leftShiftPressed = true;
                cameraSpeed = 0.1f;
            }
            if (action == GLFW_RELEASE)
            {
                leftShiftPressed = false;
                cameraSpeed = 0.05f;
            }
        }
        default: break;
    }
}

void CameraCallback::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    Camera* camera = (Camera*)glfwGetWindowUserPointer(window);
    camera->setCameraPerspective(60.0f, width / (float)height, 0.1f, 100.0f);
    camera->setResolution(width, height);
    // Redraw scene
}
