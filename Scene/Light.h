#pragma once
#include "Model.h"

struct Light
{

    Light();
    Model *mesh;
    
    glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
    
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    bool hasAttenuation = false;

};

static Model* ConstructCube();