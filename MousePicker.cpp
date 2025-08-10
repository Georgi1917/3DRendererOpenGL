#include "MousePicker.h"
#include <iostream>

MousePicker::MousePicker(GLFWwindow *window, Camera *cam, glm::mat4 projectionMatrix)
{

    glfwWindow = window;
    camera = cam;
    projMatrix = projectionMatrix;

}

MousePicker::~MousePicker()
{

}

void MousePicker::Update()
{

    currentRay = CalculateRay();

}

glm::vec3 MousePicker::CalculateRay()
{

    double mouseXPos, mouseYPos;
    glfwGetCursorPos(glfwWindow, &mouseXPos, &mouseYPos);
    glm::vec2 normalizedCoords = NormalizeMouseCoords(mouseXPos, mouseYPos);
    glm::vec4 clipCoords = glm::vec4(normalizedCoords.x, normalizedCoords.y, -1.0f, 1.0f);
    glm::vec4 eyeCoords = ToEyeCoords(clipCoords);
    glm::vec3 worldRay = ToWorldCoords(eyeCoords);
    return worldRay;

}

glm::vec3 MousePicker::ToWorldCoords(glm::vec4 eyeCoords)
{

    glm::mat4 inverted = glm::inverse(camera->GetViewMatrix());
    glm::vec4 rayWorld = inverted * eyeCoords;
    glm::vec3 mouseRay = glm::vec3(rayWorld.x, rayWorld.y, rayWorld.z);
    glm::vec3 normalized = glm::normalize(mouseRay);
    return normalized;

}

glm::vec4 MousePicker::ToEyeCoords(glm::vec4 clipCoords)
{

    glm::mat4 inverted = glm::inverse(projMatrix);
    glm::vec4 eyeCoords = inverted * clipCoords;
    return glm::vec4(eyeCoords.x, eyeCoords.y, -1.0f, 0.0f);

}

glm::vec2 MousePicker::NormalizeMouseCoords(double mouseX, double mouseY)
{

    double normalizedX = 2.0 * (mouseX / 1280.0) - 1.0;
    double normalizedY = 1.0 - 2.0 * (mouseY / 720.0);
    return glm::vec2(normalizedX, normalizedY);

}

glm::vec3 MousePicker::GetCurrentRay()
{
    return currentRay;
}