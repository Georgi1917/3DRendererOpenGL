#include "FilePanel.h"
#include "../include/imgui/imgui.h"
#include "../include/imgui/imgui_impl_glfw.h"
#include "../include/imgui/imgui_impl_opengl3.h"
#include <filesystem>
#include <iostream>

void FilePanel::OnRender(const char* name, Scene& scene)
{

    ImGui::Begin(name);

    static bool inside_folder = false;
    static std::string path = ".\\Resources";

    if (inside_folder) {
        if (ImGui::Button("<< Back")) {
            path = ".\\Resources";
            inside_folder = false;
        }
    }

    for (const auto& entry : std::filesystem::directory_iterator(path))
    {

        if (entry.is_regular_file()) {
            ImGui::Text(entry.path().filename().generic_string().c_str());
        }

        if (entry.is_directory())
        {
            if (ImGui::Button(entry.path().generic_string().c_str())) {
                inside_folder = true;
                path = entry.path().generic_string().c_str();
            }
        }

    }

    ImGui::End();

}
