#include "SceneViewport.h"
#include <iostream>

void SceneViewport::OnRender(const char* name, PickingFramebuffer &fbo, FramebufferSpecification &spec)
{

    ImGui::Begin(name);

    ImVec2 size = ImGui::GetContentRegionAvail();

    if (size.x != spec.width || size.y != spec.height)
    {

        spec.width = size.x;
        spec.height = size.y;
        fbo.ResizeFramebuffer(spec);

    }

    ImGui::Image((ImTextureID)fbo.framebufferId, size, ImVec2(0,1), ImVec2(1, 0));

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}