#include "FilePanel.h"
#include "../include/imgui/imgui.h"
#include "../include/imgui/imgui_impl_glfw.h"
#include "../include/imgui/imgui_impl_opengl3.h"
#include <filesystem>
#include <iostream>
#include "Fonts/IconsFontAwesome7.h"

inline const std::set<std::string> valid_formats_models = { ".obj", ".blend", ".stl", ".fbx", ".glb", ".gltf" };
inline const std::set<std::string> valid_formats_textures = { ".jpg", ".jpeg", ".png" };

static bool is_valid_file(std::string filepath)
{

    int idx = filepath.find('.', 0);

    std::string s = "";

    for (int i = idx; i < filepath.size(); i++) {
        s += filepath[i];
    }

    return (valid_formats_models.find(s) != valid_formats_models.end()) || (valid_formats_textures.find(s) != valid_formats_textures.end());

}

static bool icon_text_button(const char* id, 
                             const char* icon, 
                             const char* label, 
                             ImVec2 size = ImVec2(90.0f, 80.0f)) 
{

    ImGui::PushID(id);

    ImVec2 pos = ImGui::GetCursorScreenPos();

    bool clicked = ImGui::InvisibleButton("##button", size);

    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    ImVec2 min = pos;
    ImVec2 max = ImVec2(pos.x + size.x, pos.y + size.y);

    bool hovered = ImGui::IsItemHovered();
    bool active = ImGui::IsItemActive();

    ImU32 bg_color = IM_COL32(45, 45, 50, 255);

    if (hovered) {
        bg_color = IM_COL32(65, 105, 150, 255);
    } else if (active) {
        bg_color = IM_COL32(65, 65, 72, 255);
    }

    draw_list->AddRectFilled(min, max, bg_color, 6.0f);

    ImVec2 icon_size = ImGui::CalcTextSize(icon);

    ImVec2 icon_pos(
        pos.x + (size.x - icon_size.x) * 0.5f,
        pos.y + 10.0f
    );

    draw_list->AddText(icon_pos, IM_COL32(220, 220, 230, 255), icon);

    const float padding = 5.0f;
    const float text_top = pos.y + 35.0f;
    const float text_bottom = max.y - 4.0f;

    ImVec2 text_min(pos.x + padding, text_top);
    ImVec2 text_max(max.x - padding, text_bottom);

    draw_list->PushClipRect(text_min, text_max, true);

    draw_list->AddText(
        ImGui::GetFont(),
        ImGui::GetFontSize(),
        text_min,
        IM_COL32(240, 240, 240, 255),
        label,
        nullptr,
        size.x - padding * 2.0f
    );

    draw_list->PopClipRect();

    if (hovered) {
        ImGui::BeginTooltip();
        ImGui::TextUnformatted(label);
        ImGui::EndTooltip();
    }

    ImGui::PopID();

    return clicked;

}

void FilePanel::Init() {

    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontDefaultVector();

    ImFontConfig font_config;
    font_config.MergeMode = true;
    font_config.GlyphMinAdvanceX = 25.0f;

    ImFont* font = io.Fonts->AddFontFromFileTTF("ImGUILayer/Fonts/Font Awesome 7 Free-Solid-900.otf", 
                                                20.0f, &font_config);

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
        ImGui::NewLine();
    }

    for (const auto& entry : std::filesystem::directory_iterator(path))
    {

        ImGui::PushID(entry.path().generic_string().c_str());
        ImGui::SameLine();

        if (entry.is_regular_file()) {

            if (is_valid_file(entry.path().filename().generic_string()) &&
                icon_text_button("item", ICON_FA_CUBE, entry.path().filename().generic_string().c_str())) {

                scene.entities.push_back(new Model(entry.path().generic_string().c_str()));

            }
        }

        if (entry.is_directory())
        {
            
            std::string icon = ICON_FA_FOLDER;
            std::string dir  = entry.path().generic_string().c_str();

            if (icon_text_button("model", icon.c_str(), entry.path().filename().generic_string().c_str())) {
                inside_folder = true;
                path = entry.path().generic_string().c_str();
            }

        }

        ImGui::PopID();

    }

    ImGui::End();

}
