#pragma once
#define GLEW_STATIC
#include "../include/glew.h"
#include "../include/GLFW/glfw3.h"


struct Window
{

    GLFWwindow *window;
    int width;
    int height;

    Window(int width, int height, const char* title);

    void PollEvents();
    void SwapBuffers();
    void Terminate();
    void HandleResize(int width, int height);
    bool ShouldClose();

    static void FramebufferResizeCallback(GLFWwindow *window, int width, int height);

};