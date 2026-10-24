#pragma once
#define GLEW_STATIC
#include "../include/glew.h"
#include "../include/stb_image.h"
#include <string>

struct Texture
{
    
    unsigned int textureID = 0;
    std::string loc;
    std::string textureType;
    bool loaded_correctly = true;

    Texture(const char* loc, std::string texType, bool flip = true);
    //Texture(std::string texType);
    ~Texture();

    void Bind();
    void Unbind();

};