#pragma once
#define GLEW_STATIC
#include "../include/glew.h"
#include "../include/stb_image.h"
#include <string>

struct Texture
{
    
    unsigned int textureID;
    std::string textureType;

    Texture(const char* loc, std::string texType);
    ~Texture();
    void Bind();
    void Unbind();

};