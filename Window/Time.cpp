#include "Time.h"

float GetDeltaTime()
{

    float currTime = glfwGetTime();
    float deltaTime = currTime - lastTime;
    lastTime = currTime;

    return deltaTime;

}