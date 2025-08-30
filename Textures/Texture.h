#pragma once
#define GLEW_STATIC
#include "../include/glew.h"
#include "../include/stb_image.h"

class Texture
{

    private:
        unsigned int textureID;

    public:

        Texture(const char* loc);
        ~Texture();
        void Bind();
        void Unbind();

};