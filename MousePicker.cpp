#include "MousePicker.h"
#include <iostream>

MousePicker::MousePicker(GLFWwindow *window, Camera *cam, glm::mat4 projectionMatrix)
{

    glfwWindow = window;
    camera = cam;
    projMatrix = projectionMatrix;
    currObject = nullptr;

}

MousePicker::~MousePicker()
{

}

void MousePicker::Update()
{

    currentRay = CalculateRay();
    currObject->SetTranslation(currentRay);
    objWorldToView = camera->GetViewMatrix() * glm::vec4(currObject->GetTranslation(), 1.0f);
    //std::cout << currentRay.x << " " << currentRay.y << " " << currentRay.z << "\n";

}

glm::vec3 MousePicker::CalculateRay()
{

    double mouseXPos, mouseYPos;
    glfwGetCursorPos(glfwWindow, &mouseXPos, &mouseYPos);
    glm::vec2 normalizedCoords = NormalizeMouseCoords(mouseXPos, mouseYPos);
    glm::vec4 clipCoords = glm::vec4(normalizedCoords.x, normalizedCoords.y, -1.0f, 1.0f);
    glm::vec4 eyeCoords = ToEyeCoords(clipCoords);
    glm::vec4 viewSpaceIntersect = glm::vec4(glm::vec3(eyeCoords) * objWorldToView.z, 1.0f);
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

void MousePicker::CheckForMouseClick(Framebuffer& fbo, std::vector<std::unique_ptr<Renderable>>& meshes)
{

    if (glfwGetMouseButton(glfwWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {

        double mx, my;
        char pixel[3];
        glfwGetCursorPos(glfwWindow, &mx, &my);
        fbo.Bind();
        glReadPixels((int)mx, 720 - (int)my, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
        fbo.Unbind();

        for (auto &mesh : meshes)
        {

            if (mesh->CompareColorAndId(pixel[0], pixel[1], pixel[2]))
            {

                std::cout << "Clicked on : " << mesh->GetClassName() << "\n";
                currObject = mesh.get();
                objWorldToView = camera->GetViewMatrix() * glm::vec4(currObject->GetTranslation(), 1.0f);

            } 
        }

    }

    if (currObject) Update();

    //if (glfwGetMouseButton(glfwWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE && currObject) currObject = nullptr;

}

Renderable* MousePicker::GetClickedObj()
{

    return currObject;

}