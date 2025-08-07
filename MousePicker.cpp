#include "MousePicker.h"
#include <iostream>

MousePicker::MousePicker(GLFWwindow *window)
{

    glfwWindow = window;
    mouseXPos = 0;
    mouseYPos = 0;

}

MousePicker::~MousePicker()
{

}

void MousePicker::NormalizeMouseCoords()
{

    mouseXPos = (double) 2 * (mouseXPos / (double)1280) - (double)1;
    mouseYPos = (double)1 - (double)2 * (mouseYPos / (double)720);

}

void MousePicker::Update()
{

    glfwGetCursorPos(glfwWindow, &mouseXPos, &mouseYPos);
    NormalizeMouseCoords();

}