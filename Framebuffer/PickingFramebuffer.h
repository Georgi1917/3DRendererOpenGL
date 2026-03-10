#pragma once
#define GLEW_STATIC
#include "../include/glew.h"
#include <iostream>

struct PickingFramebuffer
{

    unsigned int framebufferId;
    unsigned int pickingTexId;
    unsigned int renderBuffId;

    PickingFramebuffer(int width, int height);
    PickingFramebuffer();
    ~PickingFramebuffer();

    void Bind();
    void Unbind();

};
