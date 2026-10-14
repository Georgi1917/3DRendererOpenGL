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
        ImGui::PushID(model);
        if (ImGui::CollapsingHeader("Model"))
        {

            int k = 1;

            for (auto& mesh : model->modelMeshes)
            {

                ImGui::PushID(mesh);

                const char *mat_name = mesh->material.name.c_str();
                if (!mat_name)
                {
                    mat_name = ("Mesh - " + std::to_string(k++)).c_str();
                }


                ImGui::Indent(12.0f);
                if (ImGui::CollapsingHeader(mat_name))
                {

                    ImGui::InputFloat3("Ambient", &(mesh->material.ambient.x), "%.3f");
                    ImGui::InputFloat3("Diffuse", &(mesh->material.diffuse.x), "%.3f");
                    ImGui::InputFloat3("Specular", &(mesh->material.specular.x), "%.3f");

                    ImGui::Text("\nTextures:");
                    for (auto& tex: mesh->textures)
                    {

                        ImGui::PushID(tex);
                        static char buffer[256];
                        std::strcpy(buffer, tex->loc.c_str());

                        ImGui::Text(tex->textureType.c_str());
                        if(ImGui::InputText("Texture Path", buffer, sizeof(buffer)))
                        {

                            std::string texType = tex->textureType;

                            delete tex;
                            tex = new Texture(buffer, texType);

                        }

                        ImGui::PopID();

                    }

                }

                ImGui::Unindent(12.0f);

                ImGui::PopID();

            }

        }

        ImGui::PopID();
        ImGui::PopStyleVar(1);

    }
    
    ImGui::End();

}
