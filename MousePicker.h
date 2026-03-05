#pragma once
#define GLEW_STATIC
#include "include/glew.h"
#include "include/GLFW/glfw3.h"
#include "include/glm/glm.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include "include/glm/gtc/type_ptr.hpp"
#include "Framebuffer/PickingFramebuffer.h"
#include "Camera.h"
#include "Scene/Scene.h"
#include "Scene/Mesh.h"
#include "Scene/Light.h"
#include "Scene/Model.h"
#include <vector>
#include <memory>

struct MousePicker
{

    static Model* activeEntity;

    static Model* GetClickedEntity(PickingFramebuffer &fbo, Scene &scene);
    static Model* GetCurrentActiveEntity();

};