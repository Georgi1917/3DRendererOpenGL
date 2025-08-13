#pragma once
#define GLEW_STATIC
#include "../include/glew.h"

class Framebuffer
{

    private:
        unsigned int rendererId;

    public:
        Framebuffer();
        ~Framebuffer();

        void Bind();
        void Unbind();

        void CheckStatus();

};