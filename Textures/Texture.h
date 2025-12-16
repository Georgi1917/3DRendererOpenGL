#pragma once
#define GLEW_STATIC
#include "../include/glew.h"
#include "../include/stb_image.h"
#include <string>

struct Texture
{
    
    unsigned int textureID;
    std::string loc;
    std::string textureType;

    Texture(const char* loc, std::string texType, bool flip = true);
    ~Texture();
    void Bind();
    void Unbind();

};