#include "EntityControllPanel.h"

static bool IsValidFile(std::string filepath)
{

    std::set<std::string> validFormats = { ".obj", ".blend", ".stl", ".fbx", ".glb", ".gltf" };
    int idx = filepath.find('.', 0);

    std::string s = "";

    for (int i = idx; i < filepath.size(); i++)
        s += filepath[i];

    return validFormats.find(s) != validFormats.end();

}

void EntityControllPanel::OnRender(const char* name, Scene &scene)
{

    float deltaTime = GetDeltaTime();

    Model* activeEntity = MousePicker::GetCurrentActiveEntity();

    ImGui::Begin(name);

    if (ImGui::Button("Import Object"))
        ImGui::OpenPopup("Objects");

    if (ImGui::BeginPopup("Objects"))
    {

        const char *path = "obj-files/";

        for (const auto &entry : std::filesystem::directory_iterator(path))
        {

            if (IsValidFile(entry.path().string()) && ImGui::MenuItem(entry.path().generic_string().c_str()))
                scene.entities.push_back(new Model(entry.path().generic_string().c_str()));

        }

        ImGui::EndPopup();

    }

    if (ImGui::Checkbox("Attenuation", &scene.lightSource->hasAttenuation))
    {}

    if (ImGui::Checkbox("Draw Skybox", &scene.hasSkybox))
    {}
        
    if (activeEntity)
    {

        if (ImGui::Button("Delete Object"))
        {

            for (auto it = scene.entities.begin(); it != scene.entities.end();)
            {

                if (*it == activeEntity)
                {

                    delete *it;
                    it = scene.entities.erase(it);
        
                    activeEntity = nullptr;
                    MousePicker::activeEntity = nullptr;

                    break;

                }
                else it++;

            }

        }
        
    }

    if (activeEntity)
    {

        if (
            ImGui::DragFloat3("Translation", &(activeEntity->trans.x), 1.0f * deltaTime, -100, 100) ||
            ImGui::DragFloat3("Rotation", &(activeEntity->rotation.x), 10.0f, -360, 360) ||
            ImGui::DragFloat3("Scale", &(activeEntity->scale.x), 2.0f * deltaTime, 1.0f, 100.0f) 
            ) activeEntity->UpdateMatrix();

    }

    ImGui::End();

}