#pragma once
#define GLEW_STATIC
#include "../include/glew.h"
#include "../include/stb_image.h"
#include <string>
#include <vector>

struct Cubemap
{

    unsigned int cubemapID;
    Cubemap(std::vector<std::string> faces);
    
    void Bind();
    void Unbind();

};