#pragma once
#define GLEW_STATIC
#include "../include/glew.h"

class Renderbuffer
{

    private:
        unsigned int rendererId;

    public:
        Renderbuffer();
        ~Renderbuffer();

        void Bind();
        void Unbind();

};