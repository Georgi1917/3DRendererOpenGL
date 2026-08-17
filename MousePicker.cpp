#include "MousePicker.h"
#include <iostream>

Model* MousePicker::activeEntity  = nullptr;
bool MousePicker::is_dragging = false;

void MousePicker::GetClickedEntity(Framebuffer &fbo, Scene &scene)
{

    if (glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !is_dragging)
    {

        double mx, my;
        char pixel[3];
        glfwGetCursorPos(glfwGetCurrentContext(), &mx, &my);
        int mouseRelX = (int)mx - fbo.f_x;
        int mouseRelY = (int)my - fbo.f_y;

        if (mouseRelX < 0 || mouseRelY < 0 || 
            mouseRelX > fbo.f_x + fbo.f_width || mouseRelY > fbo.f_y + fbo.f_height)
            return;

        fbo.Bind();
        glReadPixels(mouseRelX, fbo.f_height - mouseRelY, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
        fbo.Unbind();

        if (scene.lightSource->mesh->CompareIdToColor(pixel[0], pixel[1], pixel[2]))
        {

            activeEntity = scene.lightSource->mesh;
            is_dragging = true;

        }

        for (auto entity : scene.entities)
        {

            if (entity->CompareIdToColor(pixel[0], pixel[1], pixel[2]))
            {
                activeEntity = entity;
                is_dragging = true;
                break;
            }
            
        }

    }

    if (glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_LEFT) != GLFW_PRESS)
        is_dragging = false;

}
