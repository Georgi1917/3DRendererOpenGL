#pragma once
#define GLEW_STATIC
#include "include/glew.h"
#include "include/GLFW/glfw3.h"
#include "include/glm/glm.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include "include/glm/gtc/type_ptr.hpp"
#include "Framebuffer/Framebuffer.h"
#include "Camera.h"
#include "Renderables/Renderable.h"
#include <vector>
#include <memory>

class MousePicker
{

    private:
        glm::vec3 currentRay;
        GLFWwindow *glfwWindow;
        glm::mat4 projMatrix;
        Camera *camera;
        Renderable *currObject;
        glm::vec3 CalculateRay();
        glm::vec2 NormalizeMouseCoords(double mouseX, double mouseY);
        glm::vec4 ToEyeCoords(glm::vec4 clipCoords);
        glm::vec3 ToWorldCoords(glm::vec4 eyeCoords);

    public:
        MousePicker(GLFWwindow *window, Camera *cam, glm::mat4 projectionMatrix);
        ~MousePicker();

        void Update();
        void CheckForMouseClick(Framebuffer &fbo, std::vector<std::unique_ptr<Renderable>> &meshes);
        Renderable* GetClickedObj();

};