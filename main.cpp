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
#include "Renderer.h"
#include "Shader.h"
#include "Camera.h"
#include "MousePicker.h"
#include "Renderables/Renderable.h"
#include "Renderables/Cube.h"
#include "Renderables/Sphere.h"
#include "Framebuffer/Framebuffer.h"
#include "Framebuffer/PickingTexture.h"
#include "Framebuffer/Renderbuffer.h"
#include "Textures/Texture.h"
#include "include/assimp/Importer.hpp"
#include "include/assimp/scene.h"
#include "include/assimp/postprocess.h"
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

    Renderer renderer;

    Framebuffer fbo;
    PickingTexture pickingTex;
    Renderbuffer rbo;

    fbo.CheckStatus();

    fbo.Unbind();

    Shader basicShader("shaders/basic.vs", "shaders/basic.fs");
    Shader lightingShader("shaders/lighting.vs", "shaders/lighting.fs");
    Shader pickingShader("shaders/picking.vs", "shaders/picking.fs");

    Camera camera(glm::vec3(1.0f, 0.0f, 4.0f), glm::vec3(0.0f, 0.0f, -1.0f));

    renderer.SetCamera(&camera);

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

    // Assimp::Importer importer;

    // const aiScene* scene = importer.ReadFile("models/simple_cube.obj", aiProcess_Triangulate | aiProcess_FlipUVs);

    // if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    // {

    //     std::cerr << "Assimp error: " << importer.GetErrorString() << std::endl;
    //     return -1;

    // }

    // std::cout << "Model loaded! Meshes: " << scene->mNumMeshes << std::endl;
    // return 0;

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

        renderer.DrawMeshes(basicShader);
        renderer.DrawLightSource(lightingShader);

        mousePicker.CheckForMouseClick(fbo, renderer.GetMeshes());
        mousePicker.CheckForLightSourceClick(fbo, renderer.GetLightSource());

        ImGui::Begin("First Window");
        if (ImGui::Button("Cube"))
        {

            renderer.AddMesh(new Cube(glm::vec3(0.5f, 0.5f, 0.5f)));

        }
        if (ImGui::Button("Sphere"))
        {

            renderer.AddMesh(new Sphere(glm::vec3(0.5f, 0.5f, 0.5f), 1.0f, 50, 50));

        }
        if (mousePicker.GetClickedObj())
        {

            const char* text = mousePicker.GetClickedObj()->GetClassName().c_str();
            ImGui::Text(text);

            if (ImGui::Button("Remove Texture"))
            {

                mousePicker.GetClickedObj()->RemoveTexture();

            }

            if (ImGui::Button("Change Texture"))
            {

                ImGui::OpenPopup("Textures");

            }

            if (ImGui::BeginPopup("Textures"))
            {

                const char *path = "texture-files/";
                for (const auto &entry : std::filesystem::directory_iterator(path))
                {

                    if(ImGui::MenuItem(entry.path().generic_string().c_str()))
                    {

                        mousePicker.GetClickedObj()->SetTexture(new Texture(entry.path().generic_string().c_str()));

                    }

                }

                if (ImGui::MenuItem("None")) mousePicker.GetClickedObj()->SetTexture(nullptr);

                ImGui::EndPopup();

            }

            if (ImGui::Button("Delete Object"))
            {

                renderer.DeleteObject(mousePicker.GetClickedObj());

            }

            ImGui::DragFloat3("Translation", &(mousePicker.GetClickedObj()->GetTranslation().x), 1.0f * deltaTime, -100, 100);
            ImGui::DragFloat3("Rotation", &(mousePicker.GetClickedObj()->GetRotation().x), 10.0f, -360, 360);
            ImGui::DragFloat3("Scale", &(mousePicker.GetClickedObj()->GetScale().x), 2.0f * deltaTime, 1.0f, 100.0f);
            ImGui::ColorPicker3("Color", &(mousePicker.GetClickedObj()->GetColor().r));
            
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