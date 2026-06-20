#pragma once
#define GLEW_STATIC
#include "../include/glew.h"
#include <iostream>

struct Framebuffer
{

    int f_x, f_y;
    int f_width, f_height;

    unsigned int framebufferId;
    unsigned int pickingTexId;
    unsigned int renderBuffId;

    Framebuffer() = default;
    Framebuffer(int x, int y, int width, int height);
    ~Framebuffer();

    void Bind();
    void Unbind();
    void ResizeFramebuffer(int x, int y, int width, int height);

};
