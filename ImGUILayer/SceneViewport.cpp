#include "SceneViewport.h"
#include <iostream>

void SceneViewport::OnRender(const char* name, Framebuffer &fbo, Scene &scene)
{

    ImGui::SetNextWindowSize({900, 600}, ImGuiCond_FirstUseEver);
    ImGui::Begin(name);

    ImGuiIO& io = ImGui::GetIO();

    ImVec2 size = ImGui::GetContentRegionAvail();
    ImVec2 pos  = ImGui::GetCursorScreenPos();

    width = size.x; height = size.y;
    x = pos.x; y = pos.y;

    if (size.x != fbo.f_width || size.y != fbo.f_height)
    {
        fbo.ResizeFramebuffer(x, y, width, height);
        scene.ResetProjection(width, height);
    }

    ImGui::Image((ImTextureID)fbo.pickingTexId, size, ImVec2(0,1), ImVec2(1, 0));

    guizmo_layer.BeginFrame(x, y, width, height);
    guizmo_layer.UpdateEntity(scene.camera->GetViewMatrix(), scene.projection);

    if(ImGui::BeginDragDropTarget()) {
        if(const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ITEM")) {
            const char* path = (const char*)payload->Data;

            scene.entities.push_back(new Model(path));
        }

        ImGui::EndDragDropTarget();
    }

    ImGui::End();

}