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
#include "Renderables/Cube.h"
#include "Renderables/Sphere.h"
#include "Framebuffer/Framebuffer.h"
#include "Framebuffer/PickingTexture.h"
#include "Framebuffer/Renderbuffer.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

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

    std::vector<Renderable*> meshes;

    Cube cube(1, glm::vec3(1.0f, 0.0f, 0.0f));
    Sphere sphere(2, glm::vec3(1.0f, 0.0f, 0.0f), 1.0f, 50, 50);

    meshes.push_back(&cube);
    meshes.push_back(&sphere);

    Framebuffer fbo;
    PickingTexture pickingTex;
    Renderbuffer rbo;

    fbo.CheckStatus();

    fbo.Unbind();

    Shader basicShader("shaders/vertex.shader", "shaders/fragment.shader");

    glm::mat4 projection;

    projection = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 1.0f, 100.0f);

    basicShader.SetMatrix4fv("projection", projection);

    Renderer renderer;
    Camera camera(glm::vec3(1.0f, 0.0f, 4.0f), glm::vec3(0.0f, 0.0f, -1.0f));
    MousePicker mousePicker(window, &camera, projection);

    renderer.EnableDepthTesting();

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, nullptr);

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
        mousePicker.Update();

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, translation);
        model = glm::rotate(model, glm::radians(angle.x), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(angle.y), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(angle.z), glm::vec3(0.0f, 0.0f, 1.0f));

        basicShader.SetMatrix4fv("model", model);

        renderer.DrawPicking(&cube, basicShader, GL_TRIANGLES, 0);

        glm::mat4 sphereModel = glm::mat4(1.0f);
        sphereModel = glm::translate(sphereModel, glm::vec3(2.0f, 0.0f, 0.0f));

        basicShader.SetMatrix4fv("model", sphereModel);

        renderer.DrawPicking(&sphere, basicShader, GL_TRIANGLES, GL_UNSIGNED_INT);

        fbo.Unbind();

        renderer.SetViewport(0, 0, 1280, 720);
        renderer.Clear();

        basicShader.SetMatrix4fv("model", model);

        renderer.Draw(&cube, basicShader, GL_TRIANGLES, 0);

        basicShader.SetMatrix4fv("model", sphereModel);

        renderer.Draw(&sphere, basicShader, GL_TRIANGLES, GL_UNSIGNED_INT);

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {

            double mx, my;
            unsigned char pixels[3];
            glfwGetCursorPos(window, &mx, &my);
            fbo.Bind();
            glReadPixels((int)mx, 720 - (int)my, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixels);
            fbo.Unbind();
            if (cube.CompareColorAndId(pixels[0], pixels[1], pixels[2])) std::cout << "Clicked on Cube" << "\n";
            else if (sphere.CompareColorAndId(pixels[0], pixels[1], pixels[2])) std::cout << "Clicked on sphere" << "\n";
            else std::cout << "Clicked on empty space" << "\n";

        }

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