#include "MousePicker.h"
#include <iostream>

Model* MousePicker::activeEntity = nullptr;

Model* MousePicker::GetClickedEntity(Framebuffer &fbo, Scene &scene)
{

    if (glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {

        double mx, my;
        char pixel[3];
        glfwGetCursorPos(glfwGetCurrentContext(), &mx, &my);
        fbo.Bind();
        glReadPixels((int)mx, GetCurrentContext()->height - (int)my, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
        fbo.Unbind();

        if (scene.lightSource->mesh->CompareIdToColor(pixel[0], pixel[1], pixel[2]))
        {

            activeEntity = scene.lightSource->mesh;

        }

        for (auto entity : scene.entities)
        {

            if (entity->CompareIdToColor(pixel[0], pixel[1], pixel[2]))
            {
                activeEntity = entity;
                break;
            }
            
        }

    }

    return activeEntity;

}

Model* MousePicker::GetCurrentActiveEntity()
{

    return activeEntity;

}
