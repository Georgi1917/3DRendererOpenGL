#pragma once
#define GLEW_STATIC
#include "../include/glew.h"
#include "../include/stb_image.h"

struct Texture
{
    
    unsigned int textureID;

    Texture(const char* loc);
    ~Texture();
    void Bind();
    void Unbind();

};