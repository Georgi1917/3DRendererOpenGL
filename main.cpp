#define GLEW_STATIC
#include "include/imgui/imgui.h"
#include "include/imgui/imgui_impl_glfw.h"
#include "include/imgui/imgui_impl_opengl3.h"
#include "include/glew.h"
#include "include/GLFW/glfw3.h"
#include "include/glm/glm.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include "include/glm/gtc/type_ptr.hpp"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "BufferLayoutObject.h"
#include "Shader.h"
#include "Camera.h"
#include "MousePicker.h"
#include "Renderer.h"
#include "Framebuffer/Framebuffer.h"
#include "Framebuffer/PickingTexture.h"
#include "Framebuffer/Renderbuffer.h"
#include "Textures/Texture.h"
#include "Textures/Cubemap.h"
#include "include/stb_image.h"
#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <filesystem>

float deltaTime = 0.0f;
float lastTime = 0.0f;

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

    GLFWwindow *window;

    if (!glfwInit())
    {
        return -1;
    }

    window = glfwCreateWindow(1280, 720, "Renderer", NULL, NULL);

    if(!window)
    {
        return -1;
    }

    glfwMakeContextCurrent(window);
    glewInit();

    std::vector<std::string> faces = {

        "cubemap-faces/right.jpg",
        "cubemap-faces/left.jpg",
        "cubemap-faces/top.jpg",
        "cubemap-faces/bottom.jpg",
        "cubemap-faces/front.jpg",
        "cubemap-faces/back.jpg",

    };

    Framebuffer fbo;
    PickingTexture pickingTex;
    Renderbuffer rbo;

    fbo.CheckStatus();

    fbo.Unbind();

    Shader basicShader("shaders/basic.vs", "shaders/basic.fs");
    Shader lightingShader("shaders/lighting.vs", "shaders/lighting.fs");
    Shader pickingShader("shaders/picking.vs", "shaders/picking.fs");
    Shader skyboxShader("shaders/skybox.vs", "shaders/skybox.fs");

    Camera camera(glm::vec3(1.0f, 0.0f, 4.0f), glm::vec3(0.0f, 0.0f, -1.0f));

    Renderer renderer;

    Cubemap cubemap;
    cubemap.Init();
    cubemap.Load(faces);

    renderer.cam = &camera;
    renderer.skyBoxTexture = &cubemap;

    MousePicker mousePicker(window, &camera, renderer.GetProjection());
    glfwSetWindowUserPointer(window, &mousePicker);
    glfwSetScrollCallback(window, MousePicker::ScrollCallback);

    renderer.EnableDepthTesting();

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, nullptr);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    bool wireFrameMode = false;

    while(!glfwWindowShouldClose(window))
    {

        fbo.Bind();
        renderer.SetViewport(0, 0, 1280, 720);
        renderer.Clear();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        float currTime = glfwGetTime();
        deltaTime = currTime - lastTime;
        lastTime = currTime;

        camera.Update(window, deltaTime);

        renderer.DrawMeshesPicking(pickingShader);
        renderer.DrawLightSourcePicking(lightingShader);

        fbo.Unbind();

        renderer.SetViewport(0, 0, 1280, 720);
        renderer.Clear();

        renderer.DrawSkybox(skyboxShader);
        renderer.DrawMeshes(basicShader);
        renderer.DrawLightSource(lightingShader);

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
        
        if (ImGui::Checkbox("Attenuation", &renderer.hasAttenuation))
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

                    }
                    else it++;

                }

            }

            if (ImGui::Checkbox("Flip UVs", &mousePicker.GetClickedObj()->uvFlipped))
            {}

            ImGui::DragFloat3("Translation", &(mousePicker.GetClickedObj()->trans.x), 1.0f * deltaTime, -100, 100);
            ImGui::DragFloat3("Rotation", &(mousePicker.GetClickedObj()->rotation.x), 10.0f, -360, 360);
            ImGui::DragFloat3("Scale", &(mousePicker.GetClickedObj()->scale.x), 2.0f * deltaTime, 1.0f, 100.0f);
            
        }
        
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);

        glfwPollEvents();

    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;

}