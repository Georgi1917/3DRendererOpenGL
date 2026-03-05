#pragma once

#include "../Scene/Model.h"

struct ImGuizmoLayer
{

    void BeginFrame(int x, int y, int width, int height);
    void UpdateEntity(Model* entity);

};