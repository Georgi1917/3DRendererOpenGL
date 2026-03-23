#pragma once

#include "../include/imgui/imgui.h"
#include "../include/imgui/imgui_impl_glfw.h"
#include "../include/imgui/imgui_impl_opengl3.h"
#include "../Framebuffer/Framebuffer.h"
#include "ImGuizmoLayer.h"

struct SceneViewport
{

    int x, y;
    int width, height;
    ImGuizmoLayer guizmo_layer;
    
    void OnRender(const char* name, Framebuffer &fbo, Scene &scene);

};