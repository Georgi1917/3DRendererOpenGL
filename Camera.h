#pragma once

#define GLEW_STATIC
#include "include/glew.h"

#include "include/glm/glm.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include "include/glm/gtc/type_ptr.hpp"
#include "include/GLFW/glfw3.h"

#include "Shader.h"

class Camera
{

    private:
    
        glm::vec3 CameraPos;
        glm::vec3 CameraFront;
        glm::vec3 CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::mat4 view = glm::mat4(1.0f);

        float yaw = -90.0f;
        float pitch = 0.0f;

        float CameraSpeed = 15.0f;
        float RotationSpeed = 60.0f;

    public:

        Camera(glm::vec3 camPos, glm::vec3 camFront);
        ~Camera();

        void Update(GLFWwindow *window, float delta);
        glm::mat4& GetViewMatrix();
        glm::vec3 GetPosition();
    
};