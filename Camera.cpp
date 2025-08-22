#include "Camera.h"
#include <iostream>

Camera::Camera(glm::vec3 camPos, glm::vec3 camFront)
{

    CameraPos = camPos;
    CameraFront = camFront;

}

Camera::~Camera()
{

}

void Camera::Update(GLFWwindow *window, float delta)
{

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        CameraPos += CameraSpeed * CameraFront * delta;
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        CameraPos -= CameraSpeed * CameraFront * delta;
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        CameraPos -= glm::normalize(glm::cross(CameraFront, CameraUp)) * CameraSpeed * delta;
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        CameraPos += glm::normalize(glm::cross(CameraFront, CameraUp)) * CameraSpeed * delta;

    if (glfwGetKey(window, GLFW_KEY_SPACE) != GLFW_PRESS)
    {

        firstMouse = true;

        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

        if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        pitch += RotationSpeed * delta;
        if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
            pitch -= RotationSpeed * delta;
        if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
            yaw += RotationSpeed * delta;
        if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
            yaw -= RotationSpeed * delta;

    }

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {

        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        double xpos;
        double ypos;

        glfwGetCursorPos(window, &xpos, &ypos);
        
        if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xOffset = xpos - lastX;
        float yOffset = lastY - ypos;
        lastX = xpos;
        lastY = ypos;

        const float sensitivity = 0.1f;

        xOffset *= sensitivity;
        yOffset *= sensitivity;

        yaw += xOffset;
        pitch += yOffset;

    }

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    CameraFront = glm::normalize(direction);

    view = glm::lookAt(CameraPos, CameraPos + CameraFront, CameraUp);

    int program;
    glGetIntegerv(GL_CURRENT_PROGRAM, &program);
    unsigned int loc = glGetUniformLocation(program, "view");
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(view));

}

glm::mat4& Camera::GetViewMatrix()
{
    return view;
}

glm::vec3 Camera::GetPosition()
{

    return CameraPos;

}