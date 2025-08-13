#pragma once
#define GLEW_STATIC
#include "../include/glew.h"

class PickingTexture
{

    private:
        unsigned int rendererId;

    public:
        PickingTexture();
        ~PickingTexture();

        void Bind();
        void Unbind();

};