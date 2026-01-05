#pragma once
#include "Model.h"

struct Light
{

    void Init();
    Model *mesh;
    
    glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

};