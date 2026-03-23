#pragma once
#define GLEW_STATIC
#include "../include/glew.h"
#include <iostream>

struct FramebufferSpecification
{

    int width, height;

};

struct Framebuffer
{

    int f_width, f_height;

    unsigned int framebufferId;
    unsigned int pickingTexId;
    unsigned int renderBuffId;

    Framebuffer() = default;
    Framebuffer(int width, int height);
    ~Framebuffer();

    void Bind();
    void Unbind();
    void ResizeFramebuffer(int width, int height);

};
