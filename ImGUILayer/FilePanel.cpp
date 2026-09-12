#include "FilePanel.h"
#include "../include/imgui/imgui.h"
#include "../include/imgui/imgui_impl_glfw.h"
#include "../include/imgui/imgui_impl_opengl3.h"
#include <filesystem>
#include <iostream>
#include "Fonts/IconsFontAwesome7.h"

void FilePanel::Init() {

    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontDefaultVector();

    ImFontConfig font_config;
    font_config.MergeMode = true;
    font_config.GlyphMinAdvanceX = 25.0f;

    ImFont* font = io.Fonts->AddFontFromFileTTF("ImGUILayer\\Fonts\\Font Awesome 7 Free-Solid-900.otf", 
                                                25.0f, &font_config);

}

void FilePanel::OnRender(const char* name, Scene& scene)
{

    ImGui::Begin(name);

    static bool inside_folder = false;
    static std::string path = ".\\Resources";

    if (inside_folder) {
        if (ImGui::Button(ICON_FA_ARROW_LEFT_LONG " Back")) {
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
            
            std::string icon = ICON_FA_FOLDER;
            std::string dir  = entry.path().generic_string().c_str();

            if (ImGui::Button((icon.append(dir)).c_str())) {
                inside_folder = true;
                path = entry.path().generic_string().c_str();
            }

        }

    }

    ImGui::End();

}
