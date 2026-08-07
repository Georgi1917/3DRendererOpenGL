#include "FilePanel.h"
#include "../include/imgui/imgui.h"
#include "../include/imgui/imgui_impl_glfw.h"
#include "../include/imgui/imgui_impl_opengl3.h"
#include <filesystem>

void FilePanel::OnRender(const char* name, Scene& scene)
{

    ImGui::Begin(name);

    const char *path = "./";

    for (const auto& entry : std::filesystem::directory_iterator(path))
    {

        if(entry.is_directory())
        {
            ImGui::Text(entry.path().generic_string().c_str());
        }

    }

    ImGui::End();

}