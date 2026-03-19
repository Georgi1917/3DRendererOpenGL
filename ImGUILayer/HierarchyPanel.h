#pragma once
#include "../Window/Window.h"
#include "../Window/Time.h"
#include "../Scene/Scene.h"
#include "../include/imgui/imgui.h"
#include "../include/imgui/imgui_impl_glfw.h"
#include "../include/imgui/imgui_impl_opengl3.h"
#include "../MousePicker.h"
#include <filesystem>
#include <string>
#include <vector>
#include <set>

struct HierarchyPanel
{

    void Init(Window window, bool install_callbacks);
    void NewFrame();
    void OnRender(const char *name, Scene &scene);
    void ShowDockspace();
    void Shutdown();

};