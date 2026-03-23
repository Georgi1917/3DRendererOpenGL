#include "ImGuizmoLayer.h"

void ImGuizmoLayer::BeginFrame(int x, int y, int width, int height, ImDrawList *drawList)
{

    ImGuizmo::BeginFrame();
    ImGuizmo::SetOrthographic(false);
    ImGuizmo::SetDrawlist(drawList);
    ImGuizmo::SetRect(x, y, width, height);

}

void ImGuizmoLayer::UpdateEntity(Model *entity, glm::mat4 &viewMatrix, glm::mat4 &projection)
{

    if (!entity)
        return;

    static bool isKeyPressedLastFrame = false;
    bool isKeyPressed = glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_F) == GLFW_PRESS;

    if (isKeyPressed && !isKeyPressedLastFrame)
    {

        if (currentOperation == ImGuizmo::TRANSLATE)
            currentOperation = ImGuizmo::ROTATE;
        else if (currentOperation == ImGuizmo::ROTATE)
            currentOperation = ImGuizmo::SCALE;
        else currentOperation = ImGuizmo::TRANSLATE;

    }

    isKeyPressedLastFrame = isKeyPressed;

    glm::mat4& model = entity->model;

    ImGuizmo::Manipulate(
        glm::value_ptr(viewMatrix),
        glm::value_ptr(projection),
        currentOperation,
        ImGuizmo::LOCAL,
        glm::value_ptr(model)
    );

    if (ImGuizmo::IsUsing())
    {

        glm::vec3 translation, rotation, scale;

        ImGuizmo::DecomposeMatrixToComponents(
            glm::value_ptr(model),
            glm::value_ptr(translation),
            glm::value_ptr(rotation),
            glm::value_ptr(scale)
        );

        entity->trans = translation;
        entity->rotation = rotation;
        entity->scale = scale;

    }

}