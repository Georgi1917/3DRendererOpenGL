#include "include/imgui/imgui.h"
#include "include/imgui/imgui_impl_glfw.h"
#include "include/imgui/imgui_impl_opengl3.h"
#include "include/imguizmo/ImGuizmo.h"
#include "Window/Window.h"
#include "Window/Time.h"
#include "Shader.h"
#include "Camera.h"
#include "MousePicker.h"
#include "Renderer/Renderer.h"
#include "Framebuffer/PickingFramebuffer.h"
#include "Textures/Texture.h"
#include "ImGUILayer/ImGuizmoLayer.h"
#include <string>
#include <iostream>
#include <vector>
#include <set>
#include <memory>
#include <filesystem>

void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                                const GLchar* message, const void* userParam) 
{
    fprintf(stderr, "OpenGL Debug: %s\n", message);
}

static bool IsValidFile(std::string filepath)
{

    std::set<std::string> validFormats = { ".obj", ".blend", ".stl", ".fbx", ".glb", ".gltf" };
    int idx = filepath.find('.', 0);

    std::string s = "";

    for (int i = idx; i < filepath.size(); i++)
        s += filepath[i];

    return validFormats.find(s) != validFormats.end();

}

int main()
{

    Window win = Window(1280, 720, "Renderer");

    std::cout << GetCurrentContext()->width << " " << GetCurrentContext()->height << "\n";

    Shader basicShader("shaders/basic.vs", "shaders/basic.fs");
    Shader lightingShader("shaders/lighting.vs", "shaders/lighting.fs");
    Shader pickingShader("shaders/picking.vs", "shaders/picking.fs");
    Shader skyboxShader("shaders/skybox.vs", "shaders/skybox.fs");

    ImGuizmoLayer ImGuizmoLayer;
    MousePicker mousePicker;
    PickingFramebuffer fbo;
    Renderer renderer; renderer.fbo = fbo;

    renderer.EnableDepthTesting();

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, nullptr);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(win.window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    bool wireFrameMode = false;
    Model* activeEntity = nullptr;

    while(!win.ShouldClose())
    {

        float deltaTime = GetDeltaTime();

        renderer.scene.camera->Update(win.window, deltaTime);

        renderer.BeginFrame();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        renderer.PickingPass(pickingShader);
        renderer.SkyboxPass(skyboxShader);
        renderer.MainPass(basicShader);
        renderer.LightPass(lightingShader);

        activeEntity = mousePicker.GetClickedEntity(fbo, renderer.scene);

        ImGuizmoLayer.BeginFrame(0, 0, win.width, win.height);
        ImGuizmoLayer.UpdateEntity(activeEntity, renderer.scene.camera->GetViewMatrix(), renderer.scene.projection);
        
        ImGui::Begin("First Window");

        if (ImGui::Button("Import Object"))
            ImGui::OpenPopup("Objects");

        if (ImGui::BeginPopup("Objects"))
        {

            const char *path = "obj-files/";

            for (const auto &entry : std::filesystem::directory_iterator(path))
            {

                if (IsValidFile(entry.path().string()) && ImGui::MenuItem(entry.path().generic_string().c_str()))
                    renderer.scene.entities.push_back(new Model(entry.path().generic_string().c_str()));

            }

            ImGui::EndPopup();

        }

        if (ImGui::Checkbox("Wireframe Mode", &wireFrameMode))
            if (wireFrameMode) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        

        if (ImGui::Checkbox("Attenuation", &renderer.scene.lightSource->hasAttenuation))
        {}

        if (ImGui::Checkbox("Draw Skybox", &renderer.scene.hasSkybox))
        {}
            
        if (activeEntity)
        {

            if (ImGui::Button("Delete Object"))
            {

                for (auto it = renderer.scene.entities.begin(); it != renderer.scene.entities.end();)
                {

                    if (*it == activeEntity)
                    {

                        delete *it;
                        it = renderer.scene.entities.erase(it);
            
                        activeEntity = nullptr;
                        mousePicker.activeEntity = nullptr;

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

        win.SwapBuffers();
        win.PollEvents();

    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    win.Terminate();
    return 0;

}