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

    Model* activeEntity = MousePicker::GetCurrentActiveEntity();

    ImGui::Begin(name);

    if (ImGui::CollapsingHeader("Header 1"))
    {

        

    }

    if (activeEntity)
    {

        ImGui::Text("\n\nMATERIAL INFO:");
        int i = 0;
        int j = 0;
        for (auto mesh : activeEntity->modelMeshes)
        {
            ImGui::Text(mesh->material.name.c_str());
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

        if (ImGui::Button("Flip Textures"))
        {
            static bool flipState = false;

            for (auto mesh : activeEntity->modelMeshes)
            {

                std::string location;
                std::string texType;
                std::vector<Texture*> flippedTextures;

                for (auto it = mesh->textures.begin(); it != mesh->textures.end();)
                {

                    location = (*it)->loc;
                    texType  = (*it)->textureType;

                    delete *it;
                    it = mesh->textures.erase(it);
                    if (location == "None") flippedTextures.push_back(new Texture(texType));
                    else flippedTextures.push_back(new Texture(location.c_str(), texType, flipState));

                }

                mesh->textures = std::move(flippedTextures);

            }

            flipState = flipState ? false : true;

        }
            
    }
    
    ImGui::End();

}
