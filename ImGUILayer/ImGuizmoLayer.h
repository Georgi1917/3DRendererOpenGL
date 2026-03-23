#pragma once

#include "../Scene/Model.h"
#include "../include/GLFW/glfw3.h"
#include "../include/imgui/imgui.h"
#include "../include/imgui/imgui_impl_glfw.h"
#include "../include/imgui/imgui_impl_opengl3.h"
#include "../include/imguizmo/ImGuizmo.h"
#include "../MousePicker.h"

struct ImGuizmoLayer
{

    ImGuizmo::OPERATION currentOperation = ImGuizmo::TRANSLATE;

    void BeginFrame(int x, int y, int width, int height);
    void UpdateEntity(glm::mat4 &viewMatrix, glm::mat4 &projection);

};