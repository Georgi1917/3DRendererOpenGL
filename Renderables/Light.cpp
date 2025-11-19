#include "Light.h"

void Light::Init()
{

    mesh = ConstructCubeM();
    mesh->scale = glm::vec3(0.5f, 0.5f, 0.5f);
    mesh->trans = glm::vec3(2.0f, 2.0f, 0.0f);
    mesh->SetUpMatrix();

    ambient = glm::vec3(0.35f, 0.35f, 0.35f);
    diffuse = glm::vec3(0.7f, 0.7f, 0.7f);
    specular = glm::vec3(1.0f, 1.0f, 1.0f);

}