#include "Window.h"

Window::Window(int width, int height, const char* title)
{

    if (!glfwInit()) throw "GLFW could not be initialized!";

    window = glfwCreateWindow(width, height, title, NULL, NULL);

    if (!window) throw "Window could not be created!";

    glfwMakeContextCurrent(window);
    glewInit();

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

bool Window::ShouldClose()
{

    return glfwWindowShouldClose(window);

}