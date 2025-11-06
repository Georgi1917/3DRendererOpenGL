#pragma once
#include "Model.h"

struct Light
{

    void Init();
    Model *mesh;
    
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

};