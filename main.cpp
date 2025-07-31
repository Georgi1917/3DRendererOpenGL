#define GLEW_STATIC
#include "include/imgui/imgui.h"
#include "include/imgui/imgui_impl_glfw.h"
#include "include/imgui/imgui_impl_opengl3.h"
#include "include/glew.h"
#include "include/GLFW/glfw3.h"
#include "include/glm/glm.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include "include/glm/gtc/type_ptr.hpp"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 4.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

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

    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f), 
        glm::vec3( 2.0f,  5.0f, -15.0f), 
        glm::vec3(-1.5f, -2.2f, -2.5f),  
        glm::vec3(-3.8f, -2.0f, -12.3f),  
        glm::vec3( 2.4f, -0.4f, -3.5f),  
        glm::vec3(-1.7f,  3.0f, -7.5f),  
        glm::vec3( 1.3f, -2.0f, -2.5f),  
        glm::vec3( 1.5f,  2.0f, -2.5f), 
        glm::vec3( 1.5f,  0.2f, -1.5f), 
        glm::vec3(-1.3f,  1.0f, -1.5f)  
    };

    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

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

    glEnable(GL_DEPTH_TEST);

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

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
        glDrawArrays(GL_TRIANGLES, 0, 36);

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