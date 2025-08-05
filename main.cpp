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
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 4.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

std::vector<float> sphereVertices;
std::vector<unsigned int> sphereIndices;

float deltaTime = 0.0f;
float lastTime = 0.0f;

float yaw = -90.0f;
float pitch = 0.0f;

void UpdateCameraPosition(GLFWwindow *window)
{

    float cameraSpeed = 15.0f;
    float rotationSpeed = 60.0f;

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront * deltaTime;
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront * deltaTime;
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * deltaTime;
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * deltaTime;

    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        pitch += rotationSpeed * deltaTime;
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        pitch -= rotationSpeed * deltaTime;
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        yaw += rotationSpeed * deltaTime;
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        yaw -= rotationSpeed * deltaTime;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);

}

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

std::string GetShaderSources(std::string &source)
{

    std::ifstream f(source);
    std::string line;
    std::stringstream out;

    while(std::getline(f, line))
        out << line << "\n";

    return out.str();

}

int CreateProgram(std::string &vs, std::string &fs)
{

    unsigned int vertex, fragment;
    int program;
    vertex = glCreateShader(GL_VERTEX_SHADER);
    fragment = glCreateShader(GL_FRAGMENT_SHADER);

    const char *vsrc = vs.c_str();
    const char *fsrc = fs.c_str();

    glShaderSource(vertex, 1, &vsrc, nullptr);
    glShaderSource(fragment, 1, &fsrc, nullptr);

    glCompileShader(vertex);
    glCompileShader(fragment);

    program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return program;

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

    std::string vs = "shaders/vertex.shader";
    std::string fs = "shaders/fragment.shader";

    std::string vsSource = GetShaderSources(vs);
    std::string fsSource = GetShaderSources(fs);

    int program = CreateProgram(vsSource, fsSource);

    glUseProgram(program);

    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection;

    projection = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 1.0f, 100.0f);

    int vLoc = glGetUniformLocation(program, "view");
    int pLoc = glGetUniformLocation(program, "projection");
    glUniformMatrix4fv(pLoc, 1, GL_FALSE, glm::value_ptr(projection));

    Renderer renderer;

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

        UpdateCameraPosition(window);

        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        glUniformMatrix4fv(vLoc, 1, GL_FALSE, glm::value_ptr(view));

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, translation);
        model = glm::rotate(model, glm::radians(angle.x), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(angle.y), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(angle.z), glm::vec3(0.0f, 0.0f, 1.0f));

        int mLoc = glGetUniformLocation(program, "model");
        glUniformMatrix4fv(mLoc, 1, GL_FALSE, glm::value_ptr(model));

        renderer.DrawArrays(cubeVAO, GL_TRIANGLES, 0, 36);

        glm::mat4 sphereModel = glm::mat4(1.0f);
        sphereModel = glm::translate(sphereModel, glm::vec3(2.0f, 0.0f, 0.0f));

        glUniformMatrix4fv(mLoc, 1, GL_FALSE, glm::value_ptr(sphereModel));

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