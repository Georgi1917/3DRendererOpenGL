#pragma once
#include "include/GLFW/glfw3.h"

struct Window
{

    GLFWwindow *window;
    const char *title;
    int width;
    int height;

};