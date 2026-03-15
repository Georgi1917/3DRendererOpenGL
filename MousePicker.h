#pragma once
#define GLEW_STATIC
#include "include/glew.h"
#include "include/GLFW/glfw3.h"
#include "Window/Window.h"
#include "Framebuffer/PickingFramebuffer.h"
#include "Scene/Scene.h"
#include <vector>
#include <memory>

struct MousePicker
{

    static Model* activeEntity;

    static Model* GetClickedEntity(PickingFramebuffer &fbo, Scene &scene);
    static Model* GetCurrentActiveEntity();

};