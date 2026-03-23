#include "SceneViewport.h"
#include <iostream>

void SceneViewport::OnRender(const char* name, PickingFramebuffer &fbo, FramebufferSpecification &spec)
{

    ImGui::Begin(name);

    ImVec2 size = ImGui::GetContentRegionAvail();
    ImVec2 pos  = ImGui::GetCursorScreenPos();

    width = size.x; height = size.y;
    x = pos.x; y = pos.y;

    if (size.x != spec.width || size.y != spec.height)
    {

        spec.width = size.x;
        spec.height = size.y;
        fbo.ResizeFramebuffer(spec);

    }

    ImGui::Image((ImTextureID)fbo.framebufferId, size, ImVec2(0,1), ImVec2(1, 0));

    drawList = ImGui::GetWindowDrawList();

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}