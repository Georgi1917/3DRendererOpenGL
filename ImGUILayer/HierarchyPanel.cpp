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

void HierarchyPanel::Init(Window window, bool install_callbacks)
{

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window.window, install_callbacks);
    ImGui_ImplOpenGL3_Init("#version 330");

}

void HierarchyPanel::NewFrame()
{

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

}

void HierarchyPanel::OnRender(const char *name, Scene &scene)
{

    float deltaTime = GetDeltaTime();

    Model* activeEntity = MousePicker::GetCurrentActiveEntity();

    ImGui::Begin("First Window");

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

                flipState = flipState ? false : true;

                mesh->textures = std::move(flippedTextures);

            }

        }
        
    }
    
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

void HierarchyPanel::ShowDockspace()
{

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

    const ImGuiViewport *viewport = ImGui::GetMainViewport();

    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);

    window_flags |= ImGuiWindowFlags_NoTitleBar |
                    ImGuiWindowFlags_NoCollapse |
                    ImGuiWindowFlags_NoResize |
                    ImGuiWindowFlags_NoMove |
                    ImGuiWindowFlags_NoBringToFrontOnFocus |
                    ImGuiWindowFlags_NoNavFocus;

    ImGui::Begin("Dock Space", nullptr, window_flags);

    ImGuiID dockspace_id = ImGui::GetID("MainDockSpace");
    ImGui::DockSpace(dockspace_id, ImVec2(0, 0));

    ImGui::End();

}

void HierarchyPanel::Shutdown()
{

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

}