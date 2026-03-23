#pragma once
#define GLEW_STATIC
#include "include/glew.h"
#include "include/GLFW/glfw3.h"
#include "Window/Window.h"
#include "Framebuffer/Framebuffer.h"
#include "Scene/Scene.h"
#include <vector>

struct MousePicker
{

    static Model* activeEntity;

    static Model* GetClickedEntity(Framebuffer &fbo, Scene &scene);
    static Model* GetCurrentActiveEntity();

};