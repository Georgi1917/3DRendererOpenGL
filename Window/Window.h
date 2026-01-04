#pragma once
#define GLEW_STATIC
#include "../include/glew.h"
#include "../include/GLFW/glfw3.h"


struct Window
{

    GLFWwindow *window;

    Window(int width, int height, const char* title);

    void PollEvents();
    void SwapBuffers();
    void Terminate();
    bool ShouldClose();

};