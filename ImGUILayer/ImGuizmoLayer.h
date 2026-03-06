#pragma once

#include "../Scene/Model.h"
#include "../include/imgui/imgui.h"
#include "../include/imgui/imgui_impl_glfw.h"
#include "../include/imgui/imgui_impl_opengl3.h"
#include "../include/imguizmo/ImGuizmo.h"

struct ImGuizmoLayer
{

    void BeginFrame(int x, int y, int width, int height);
    void UpdateEntity(Model* entity);

};