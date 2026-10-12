#pragma once
#include "../Window/Window.h"
#include "../Window/Time.h"
#include "../Scene/Scene.h"
#include "../include/imgui/imgui.h"
#include "../include/imgui/imgui_impl_glfw.h"
#include "../include/imgui/imgui_impl_opengl3.h"
#include "../include/imguizmo/ImGuizmo.h"
#include "../MousePicker.h"
#include <filesystem>
#include <string>
#include <vector>
#include <set>

struct EntityControllPanel
{

    void OnRender(const char* name, Scene& scene);

};