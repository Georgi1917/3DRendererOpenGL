#include "HierarchyPanel.h"

static bool IsValidFile(std::string filepath)
{

    std::set<std::string> validFormats = { ".obj", ".blend", ".stl", ".fbx", ".glb", ".gltf" };
    int idx = filepath.find('.', 0);

    std::string s = "";

    for (int i = idx; i < filepath.size(); i++)
        s += filepath[i];

    return validFormats.find(s) != validFormats.end();

}

void HierarchyPanel::OnRender(const char *name, Scene &scene)
{

    float deltaTime = GetDeltaTime();

    Model* activeEntity = MousePicker::activeEntity;

    ImGui::Begin(name);

    for (auto& model : scene.entities)
    {

        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5.0f);
        if (ImGui::CollapsingHeader(("Model " + std::to_string(model->id)).c_str()))
        {

            for (auto& mesh : model->modelMeshes)
            {

                int i = 0;
                int j = 0;

                ImGui::Indent(12.0f);
                if (ImGui::CollapsingHeader(mesh->material.name.c_str()))
                {

                    ImGui::InputFloat3(("Ambient" + std::to_string(j + 1)).c_str(), &(mesh->material.ambient.x), "%.3f");
                    ImGui::InputFloat3(("Diffuse" + std::to_string(j + 1)).c_str(), &(mesh->material.diffuse.x), "%.3f");
                    ImGui::InputFloat3(("Specular" + std::to_string(j + 1)).c_str(), &(mesh->material.specular.x), "%.3f");

                    ImGui::Text("\nTextures:");
                    for (auto& tex: mesh->textures)
                    {

                        static char buffer[256];
                        std::strcpy(buffer, tex->loc.c_str());

                        ImGui::Text(tex->textureType.c_str());
                        if(ImGui::InputText(("Texture Location" + std::to_string(i + 1)).c_str(), buffer, sizeof(buffer)))
                        {

                            std::string texType = tex->textureType;

                            delete tex;
                            tex = new Texture(buffer, texType);

                        }

                        i++;

                    }

                    j++;

                }

                ImGui::Unindent(12.0f);

            }

        }

        ImGui::PopStyleVar(1);

    }
    
    ImGui::End();

}
