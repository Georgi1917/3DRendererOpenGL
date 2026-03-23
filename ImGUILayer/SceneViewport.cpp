#include "SceneViewport.h"
#include <iostream>

void SceneViewport::OnRender(const char* name, Framebuffer &fbo, Scene &scene)
{

    ImGui::Begin(name);

    ImVec2 size = ImGui::GetContentRegionAvail();
    ImVec2 pos  = ImGui::GetCursorScreenPos();

    width = size.x; height = size.y;
    x = pos.x; y = pos.y;

    if (size.x != fbo.f_width || size.y != fbo.f_height)
        fbo.ResizeFramebuffer(width, height);

    ImGui::Image((ImTextureID)fbo.framebufferId, size, ImVec2(0,1), ImVec2(1, 0));

    guizmo_layer.BeginFrame(x, y, width, height);
    guizmo_layer.UpdateEntity(scene.camera->GetViewMatrix(), scene.projection);

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}