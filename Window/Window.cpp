#include "Window.h"
#include <iostream>

Window *currentWindow = nullptr;

Window* GetCurrentContext()
{

    return currentWindow;

}

Window::Window(int width, int height, const char* title) : width(width), height(height)
{

    if (!glfwInit()) throw "GLFW could not be initialized!";

    window = glfwCreateWindow(width, height, title, NULL, NULL);

    if (!window) throw "Window could not be created!";

    glfwMakeContextCurrent(window);
    glewInit();

    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, FramebufferResizeCallback);
    currentWindow = this;

}

void Window::FramebufferResizeCallback(GLFWwindow *window, int width, int height)
{

    Window *instance = (Window*)(glfwGetWindowUserPointer(window));

    if (instance)
    {

        instance->HandleResize(width, height);

    }

}

void Window::PollEvents()
{

    glfwPollEvents();

}

void Window::SwapBuffers()
{

    glfwSwapBuffers(window);

}

void Window::Terminate()
{

    glfwTerminate();

}

void Window::HandleResize(int width, int height)
{

    this->width  = width;
    this->height = height;

}

bool Window::ShouldClose()
{

    return glfwWindowShouldClose(window);

}