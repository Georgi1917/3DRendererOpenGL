#include "include/imgui/imgui.h"
#include "include/imgui/imgui_impl_glfw.h"
#include "include/imgui/imgui_impl_opengl3.h"
#include "Window/Window.h"
#include "Window/Time.h"
#include "include/glm/glm.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include "include/glm/gtc/type_ptr.hpp"
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/BufferLayoutObject.h"
#include "Shader.h"
#include "Camera.h"
#include "MousePicker.h"
#include "Renderer/Renderer.h"
#include "Framebuffer/PickingFramebuffer.h"
#include "Textures/Texture.h"
#include "Textures/Cubemap.h"
#include "include/stb_image.h"
#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <filesystem>

void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                                const GLchar* message, const void* userParam) 
{
    fprintf(stderr, "OpenGL Debug: %s\n", message);
}

bool EndsWithObj(std::string filepath)
{

    int idx = filepath.find('.', 0);

    std::string s = "";

    for (int i = idx; i < filepath.size(); i++)
        s += filepath[i];

    return s == ".obj";

}

int main()
{

    Window win = Window(1280, 720, "Renderer");

    PickingFramebuffer fbo;

    Shader basicShader("shaders/basic.vs", "shaders/basic.fs");
    Shader lightingShader("shaders/lighting.vs", "shaders/lighting.fs");
    Shader pickingShader("shaders/picking.vs", "shaders/picking.fs");
    Shader skyboxShader("shaders/skybox.vs", "shaders/skybox.fs");

    Camera camera(glm::vec3(1.0f, 0.0f, 4.0f), glm::vec3(0.0f, 0.0f, -1.0f));

    Renderer renderer;

    Cubemap cubemap = Cubemap({

        "cubemap-faces/right.jpg",
        "cubemap-faces/left.jpg",
        "cubemap-faces/top.jpg",
        "cubemap-faces/bottom.jpg",
        "cubemap-faces/front.jpg",
        "cubemap-faces/back.jpg",

    });

    renderer.cam = &camera;
    renderer.skyBoxTexture = &cubemap;
    renderer.fbo = fbo;

    MousePicker mousePicker(win.window, &camera, renderer.GetProjection());
    glfwSetWindowUserPointer(win.window, &mousePicker);
    glfwSetScrollCallback(win.window, MousePicker::ScrollCallback);

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

    while(!win.ShouldClose())
    {

        float deltaTime = GetDeltaTime();

        camera.Update(win.window, deltaTime);

        renderer.BeginFrame();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        renderer.PickingPass(pickingShader);
        renderer.SkyboxPass(skyboxShader);
        renderer.MainPass(basicShader);
        renderer.LightPass(lightingShader);

        mousePicker.CheckForMouseClick(fbo, renderer.models_c);
        mousePicker.CheckForLightSourceClick(fbo, renderer.source->mesh);
        
        ImGui::Begin("First Window");

        if (ImGui::Button("Cube"))
            renderer.models_c.push_back(ConstructCubeM());

        if (ImGui::Button("Sphere"))
            renderer.models_c.push_back(ConstructSphereM());

        if (ImGui::Button("Pyramid"))
            renderer.models_c.push_back(ConstructPyramidM());

        if (ImGui::Button("Import Object"))
            ImGui::OpenPopup("Objects");

        if (ImGui::BeginPopup("Objects"))
        {

            const char *path = "obj-files/";

            for (const auto &entry : std::filesystem::directory_iterator(path))
            {

                if (EndsWithObj(entry.path().string()) && ImGui::MenuItem(entry.path().generic_string().c_str()))
                    renderer.models_c.push_back(LoadObjM(entry.path().generic_string().c_str()));

            }

            ImGui::EndPopup();

        }

        if (ImGui::Checkbox("Wireframe Mode", &wireFrameMode))
            if (wireFrameMode) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        
        if (ImGui::Checkbox("Attenuation", &renderer.source->hasAttenuation))
        {}

        if (ImGui::Checkbox("Draw Skybox", &renderer.hasSkybox))
        {}
            
        if (mousePicker.GetClickedObj())
        {

            if (ImGui::Button("Delete Object"))
            {

                for (auto it = renderer.models_c.begin(); it != renderer.models_c.end();)
                {

                    if (*it == mousePicker.GetClickedObj())
                    {

                        delete *it;
                        it = renderer.models_c.erase(it);
            
                        mousePicker.currModelData = nullptr;

                        break;

                    }
                    else it++;

                }

            }
            
        }

        if (mousePicker.GetClickedObj())
        {

            ImGui::DragFloat3("Translation", &(mousePicker.GetClickedObj()->trans.x), 1.0f * deltaTime, -100, 100);
            ImGui::DragFloat3("Rotation", &(mousePicker.GetClickedObj()->rotation.x), 10.0f, -360, 360);
            ImGui::DragFloat3("Scale", &(mousePicker.GetClickedObj()->scale.x), 2.0f * deltaTime, 1.0f, 100.0f);

            ImGui::Text("\n\nMATERIAL INFO:");
            for (auto mesh : mousePicker.GetClickedObj()->modelMeshes)
            {
                ImGui::Text(mesh->material.name.c_str());
                ImGui::InputFloat3("Ambient", &(mesh->material.ambient.x), "%.3f", ImGuiInputTextFlags_ReadOnly);
                ImGui::InputFloat3("Diffuse", &(mesh->material.diffuse.x), "%.3f", ImGuiInputTextFlags_ReadOnly);
                ImGui::InputFloat3("Specular", &(mesh->material.specular.x), "%.3f", ImGuiInputTextFlags_ReadOnly);

                ImGui::Text("\nTextures:");
                int i = 0;
                for (auto tex: mesh->textures)
                {

                    ImGui::Text(tex->textureType.c_str());
                    ImGui::InputText("Texture Location" + i++, &tex->loc[0], 40, ImGuiInputTextFlags_ReadOnly);

                }

            }

            if (ImGui::Button("Flip Textures"))
            {
                static bool flipState = false;

                for (auto mesh : mousePicker.GetClickedObj()->modelMeshes)
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
                        flippedTextures.push_back(new Texture(location.c_str(), texType, flipState));

                    }

                    flipState = flipState ? false : true;

                    mesh->textures = flippedTextures;

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