#pragma once
#define GLEW_STATIC
#include "include/glew.h"
#include "include/GLFW/glfw3.h"
#include "include/glm/glm.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include "include/glm/gtc/type_ptr.hpp"
#include "Framebuffer/PickingFramebuffer.h"
#include "Camera.h"
#include "Scene/Mesh.h"
#include "Scene/Light.h"
#include "Scene/Model.h"
#include <vector>
#include <memory>

struct MousePicker
{

    GLFWwindow *glfwWindow;

    Model *currModelData;

    MousePicker(GLFWwindow *window);
    ~MousePicker();

    void CheckForMouseClick(PickingFramebuffer &fbo, std::vector<Model*> &meshes);
    void CheckForLightSourceClick(PickingFramebuffer &fbo, Model*& source);
    Model* GetClickedObj();

};