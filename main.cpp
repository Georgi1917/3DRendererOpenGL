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
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

std::vector<float> sphereVertices;
std::vector<unsigned int> sphereIndices;

float deltaTime = 0.0f;
float lastTime = 0.0f;

void DrawSphere()
{

    float radius = 1.0f;
    unsigned int stacks = 50;
    unsigned int sectors = 50;

    for (unsigned int i = 0; i <= stacks; ++i)
    {

        float stackAngle = glm::pi<float>() / 2 - i * glm::pi<float>() / stacks;
        float xy = radius * cosf(stackAngle);
        float z = radius * sinf(stackAngle);

        for (unsigned int j = 0; j <= sectors; ++j)
        {

            float sectorAngle = j * 2 * glm::pi<float>() / sectors;

            float x = xy * cosf(sectorAngle);
            float y = xy * sinf(sectorAngle);

            sphereVertices.push_back(x);
            sphereVertices.push_back(y);
            sphereVertices.push_back(z);

            sphereVertices.push_back(1.0f);
            sphereVertices.push_back(0.0f);
            sphereVertices.push_back(0.0f);

        }

    }

    for (unsigned int i = 0; i < stacks; ++i)
    {

        unsigned int k1 = i * (sectors + 1);
        unsigned int k2 = k1 + sectors + 1;

        for (unsigned int j = 0; j < sectors; ++j, ++k1, ++k2)
        {

            if (i != 0)
            {
                sphereIndices.push_back(k1);
                sphereIndices.push_back(k2);
                sphereIndices.push_back(k1 + 1);
            }

            if (i != (stacks - 1))
            {
                sphereIndices.push_back(k1 + 1);
                sphereIndices.push_back(k2);
                sphereIndices.push_back(k2 + 1);
            }

        }

    }

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

    float positions[] = {
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
        0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
        0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,

        0.5f,  0.5f,  0.5f,  0.29f, 0.6f, 0.57f,
        0.5f,  0.5f, -0.5f,  0.29f, 0.6f, 0.57f,
        0.5f, -0.5f, -0.5f,  0.29f, 0.6f, 0.57f,
        0.5f, -0.5f, -0.5f,  0.29f, 0.6f, 0.57f,
        0.5f, -0.5f,  0.5f,  0.29f, 0.6f, 0.57f,
        0.5f,  0.5f,  0.5f,  0.29f, 0.6f, 0.57f,

        -0.5f, -0.5f, -0.5f, 1.0f, 0.6f, 0.12f, 
        0.5f, -0.5f, -0.5f,  1.0f, 0.6f, 0.12f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.6f, 0.12f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.6f, 0.12f,
        -0.5f, -0.5f,  0.5f, 1.0f, 0.6f, 0.12f,
        -0.5f, -0.5f, -0.5f, 1.0f, 0.6f, 0.12f,

        -0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 
        -0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 1.0f
    };

    VertexArray cubeVAO;
    VertexBuffer cubeVBO(positions, sizeof(positions));
    BufferLayoutObject cubeLayout;

    cubeLayout.Push<float>(3);
    cubeLayout.Push<float>(3);
    cubeVAO.AddBuffer(cubeVBO, cubeLayout);

    cubeVAO.Unbind();

    DrawSphere();

    VertexArray sphereVAO;
    VertexBuffer sphereVBO(sphereVertices.data(), sphereVertices.size() * sizeof(float));
    IndexBuffer sphereIBO(sphereIndices.data(), sphereIndices.size());
    BufferLayoutObject sphereLayout;
    
    sphereLayout.Push<float>(3);
    sphereLayout.Push<float>(3);

    sphereVAO.AddBuffer(sphereVBO, sphereLayout);

    sphereVAO.Unbind();

    Shader basicShader("shaders/vertex.shader", "shaders/fragment.shader");

    glm::mat4 projection;

    projection = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 1.0f, 100.0f);

    basicShader.SetMatrix4fv("projection", projection);

    Renderer renderer;
    Camera camera(glm::vec3(0.0f, 0.0f, 4.0f), glm::vec3(0.0f, 0.0f, -1.0f));

    renderer.EnableDepthTesting();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    glm::vec3 translation(0.0f, 0.0f, 0.0f);
    glm::vec3 angle(0.0f, 0.0f, 0.0f);

    while(!glfwWindowShouldClose(window))
    {

        renderer.Clear();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        float currTime = glfwGetTime();
        deltaTime = currTime - lastTime;
        lastTime = currTime;

        camera.Update(window, deltaTime);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, translation);
        model = glm::rotate(model, glm::radians(angle.x), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(angle.y), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(angle.z), glm::vec3(0.0f, 0.0f, 1.0f));

        basicShader.SetMatrix4fv("model", model);

        renderer.DrawArrays(cubeVAO, GL_TRIANGLES, 0, 36);

        glm::mat4 sphereModel = glm::mat4(1.0f);
        sphereModel = glm::translate(sphereModel, glm::vec3(2.0f, 0.0f, 0.0f));

        basicShader.SetMatrix4fv("model", sphereModel);

        renderer.DrawElements(sphereVAO, sphereIBO, GL_TRIANGLES, GL_UNSIGNED_INT);

        ImGui::Begin("First Window");
        ImGui::SliderFloat3("Translation", &translation.x, -1.0f, 1.0f);
        ImGui::DragFloat("X Rotation", &angle.x, 1.0f, -360.0f, 360.0f, "Rotate");
        ImGui::DragFloat("Y Rotation", &angle.y, 1.0f, -360.0f, 360.0f, "Rotate");
        ImGui::DragFloat("Z Rotation", &angle.z, 1.0f, -360.0f, 360.0f, "Rotate");
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