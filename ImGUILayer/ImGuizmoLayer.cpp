#include "ImGuizmoLayer.h"

void ImGuizmoLayer::BeginFrame(int x, int y, int width, int height)
{

    ImGuizmo::BeginFrame();
    ImGuizmo::SetDrawlist(ImGui::GetForegroundDrawList());
    ImGuizmo::SetRect(x, y, width, height);

}