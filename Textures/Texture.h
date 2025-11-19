#pragma once
#define GLEW_STATIC
#include "../include/glew.h"
#include "../include/stb_image.h"

enum TextureType
{

    AMBIENT_TEXTURE ,
    DIFFUSE_TEXTURE ,
    SPECULAR_TEXTURE

};

struct Texture
{
    
    unsigned int textureID;

    Texture(const char* loc, TextureType texType);
    ~Texture();
    void Bind();
    void Unbind();

};