#pragma once
#include "Mesh.h"
#include "../Shader.h"

struct Model
{

    std::vector<Mesh*> modelMeshes;

    glm::mat4 model = glm::mat4(1.0f);
    glm::vec3 trans = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);

    glm::vec3 color = glm::vec3(0.5f, 0.5f, 0.5f);

    Model(std::vector<Mesh*> meshes);
    void Draw(Shader &shader);
    void SetUpMatrix();

};

Model* ConstructCubeM();
Model* ConstructSphereM();
Model* ConstructPyramidM();
Model* ConstructSurfaceM();
Model* ConstructSkyboxM();
Model* LoadObjM(const char* filepath);