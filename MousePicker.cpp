#include "MousePicker.h"
#include <iostream>

void MousePicker::ScrollCallback(GLFWwindow *window, double xoffset, double yoffset)
{

    MousePicker *instance = static_cast<MousePicker*>(glfwGetWindowUserPointer(window));

    if (instance)
    {

        instance->HandleScroll(xoffset, yoffset);

    }

}

void MousePicker::HandleScroll(double xoffset, double yoffset)
{

    if (!currModelDrag) return;

    if (yoffset == -1)
    {
        objWorldToView.z -= 0.5f;
    }
    if (yoffset == 1) 
    {
        objWorldToView.z += 0.5f;
    }

}

MousePicker::MousePicker(GLFWwindow *window, Camera *cam, glm::mat4 projectionMatrix)
{

    glfwWindow = window;
    camera = cam;
    projMatrix = projectionMatrix;

    currModelDrag = nullptr;
    currModelData = nullptr;

    glfwSetScrollCallback(glfwWindow, ScrollCallback);

}

MousePicker::~MousePicker()
{

}

void MousePicker::Update()
{

    currentRay = CalculateRay();
    currModelDrag->trans = currentRay;

}

glm::vec3 MousePicker::CalculateRay()
{

    double mouseXPos, mouseYPos;
    glfwGetCursorPos(glfwWindow, &mouseXPos, &mouseYPos);
    glm::vec2 normalizedCoords = NormalizeMouseCoords(mouseXPos, mouseYPos);
    glm::vec4 clipCoords = glm::vec4(normalizedCoords.x, normalizedCoords.y, -1.0f, 1.0f);
    glm::vec4 eyeCoords = ToEyeCoords(clipCoords);
    glm::vec4 viewSpaceIntersect = glm::vec4(-(eyeCoords.x * objWorldToView.z), -(eyeCoords.y * objWorldToView.z), objWorldToView.z, 1.0f);
    glm::vec3 worldRay = ToWorldCoords(viewSpaceIntersect);
    return worldRay;

}

glm::vec3 MousePicker::ToWorldCoords(glm::vec4 eyeCoords)
{

    glm::mat4 inverted = glm::inverse(camera->GetViewMatrix());
    glm::vec4 rayWorld = inverted * eyeCoords;
    glm::vec3 mouseRay = glm::vec3(rayWorld.x, rayWorld.y, rayWorld.z);
    glm::vec3 normalized = glm::normalize(mouseRay);
    return mouseRay;

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

void MousePicker::CheckForMouseClick(PickingFramebuffer &fbo, std::vector<Model*> &models)
{

    if (glfwGetMouseButton(glfwWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !currModelDrag)
    {

        double mx, my;
        char pixel[3];
        glfwGetCursorPos(glfwWindow, &mx, &my);
        fbo.Bind();
        glReadPixels((int)mx, 720 - (int)my, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
        fbo.Unbind();

        for (auto &model : models)
        {

            if (model->CompareIdToColor(pixel[0], pixel[1], pixel[2]))
            {

                currModelDrag = model;
                currModelData = model;
                objWorldToView = camera->GetViewMatrix() * glm::vec4(currModelDrag->trans, 1.0f);

            }

        }

    }

    if (currModelDrag && glfwGetMouseButton(glfwWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) Update();

    if (glfwGetMouseButton(glfwWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE && currModelDrag) currModelDrag = nullptr;

}

void MousePicker::CheckForLightSourceClick(PickingFramebuffer& fbo, Model*& source)
{

    if (glfwGetMouseButton(glfwWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !currModelDrag)
    {

        double mx, my;
        char pixel[3];
        glfwGetCursorPos(glfwWindow, &mx, &my);
        fbo.Bind();
        glReadPixels((int)mx, 720 - (int)my, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
        fbo.Unbind();

        if (source->CompareIdToColor(pixel[0], pixel[1], pixel[2]))
        {

            currModelDrag = source;
            currModelData = source;
            objWorldToView = camera->GetViewMatrix() * glm::vec4(currModelDrag->trans, 1.0f);

        }

    }

    if (currModelDrag && glfwGetMouseButton(glfwWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) Update();

    if (glfwGetMouseButton(glfwWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE && currModelDrag) currModelDrag = nullptr;

}

Model* MousePicker::GetClickedObj()
{

    return currModelData;

}
