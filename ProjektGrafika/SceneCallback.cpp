#include "SceneCallback.h"
int SceneCallback::sceneIndex = 0;
int SceneCallback::sceneLimit = 1;//default value is 1 so just one scene is showing, if we want more scenes we need to set this value to number of scenes we want
bool SceneCallback::keyPressed = false;
void SceneCallback::onKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    switch (key)
    {
        case GLFW_KEY_RIGHT:
        {
            if (sceneIndex < (sceneLimit - 1) && !keyPressed)
            {
                sceneIndex++;
                keyPressed = true;
            }
            break;
        }
        case GLFW_KEY_LEFT: 
        {
            if (sceneIndex != 0 && !keyPressed)
            {
                sceneIndex--;
                keyPressed = true;
            }
            break;
        } 
    default: break;
    }
    if (action == GLFW_RELEASE)
    {
        keyPressed = false;
    }
}
void SceneCallback::setSceneLimit(int limit)
{
    SceneCallback::sceneLimit = limit;
}
int SceneCallback::getSceneIndex()
{
    return SceneCallback::sceneIndex;
}