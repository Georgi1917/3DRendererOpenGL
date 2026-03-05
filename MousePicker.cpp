#include "MousePicker.h"
#include <iostream>


MousePicker::MousePicker(GLFWwindow *window)
{

    glfwWindow = window;

    currModelData = nullptr;

}

MousePicker::~MousePicker()
{

}

void MousePicker::CheckForMouseClick(PickingFramebuffer &fbo, std::vector<Model*> &models)
{

    if (glfwGetMouseButton(glfwWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {

        double mx, my;
        char pixel[3];
        GLFWwindow *currContext = glfwGetCurrentContext();
        glfwGetCursorPos(currContext, &mx, &my);
        fbo.Bind();
        glReadPixels((int)mx, 720 - (int)my, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
        fbo.Unbind();

        for (auto &model : models)
        {

            if (model->CompareIdToColor(pixel[0], pixel[1], pixel[2]))
            {

                currModelData = model;

            }

        }

    }

}

void MousePicker::CheckForLightSourceClick(PickingFramebuffer& fbo, Model*& source)
{

    if (glfwGetMouseButton(glfwWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {

        double mx, my;
        char pixel[3];
        glfwGetCursorPos(glfwWindow, &mx, &my);
        fbo.Bind();
        glReadPixels((int)mx, 720 - (int)my, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
        fbo.Unbind();

        if (source->CompareIdToColor(pixel[0], pixel[1], pixel[2]))
        {

            currModelData = source;

        }

    }

}

Model* MousePicker::GetClickedObj()
{

    return currModelData;

}
