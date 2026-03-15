#pragma once
#define GLEW_STATIC
#include "../include/glew.h"
#include <iostream>

struct FramebufferSpecification
{

    int width, height;

};

struct PickingFramebuffer
{

    unsigned int framebufferId;
    unsigned int pickingTexId;
    unsigned int renderBuffId;

    PickingFramebuffer() = default;
    PickingFramebuffer(FramebufferSpecification &fbo_spec);
    ~PickingFramebuffer();

    void Bind();
    void Unbind();
    void ResizeFramebuffer(FramebufferSpecification &new_spec);

};
