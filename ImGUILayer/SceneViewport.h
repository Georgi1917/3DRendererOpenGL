#pragma once

#include "../include/imgui/imgui.h"
#include "../include/imgui/imgui_impl_glfw.h"
#include "../include/imgui/imgui_impl_opengl3.h"
#include "../Framebuffer/PickingFramebuffer.h"

struct SceneViewport
{

    int width, height;
    
    void OnRender(const char* name, PickingFramebuffer &fbo, FramebufferSpecification &spec);

};