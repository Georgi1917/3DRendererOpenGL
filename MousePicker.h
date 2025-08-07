#pragma once
#define GLEW_STATIC
#include "include/glew.h"
#include "include/GLFW/glfw3.h"
#include "include/glm/glm.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include "include/glm/gtc/type_ptr.hpp"

class MousePicker
{

    private:
        double mouseXPos;
        double mouseYPos;
        GLFWwindow *glfwWindow;
        void NormalizeMouseCoords();

    public:
        MousePicker(GLFWwindow *window);
        ~MousePicker();

        void Update();

};