#pragma once
#include "Mesh.h"

struct Light
{

    void Init();
    Mesh *mesh;
    
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

};