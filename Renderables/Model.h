#pragma once
#include "Mesh.h"
#include "../Textures/Texture.h"
#include "../Shader.h"

struct Model
{

    unsigned int id;
    Texture *tex = nullptr;

    std::vector<Mesh*> modelMeshes;

    glm::mat4 model = glm::mat4(1.0f);
    glm::vec3 trans = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);

    glm::vec3 color = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::vec3 pickingColor;

    Model(std::vector<Mesh*> meshes);
    void Draw(Shader &shader);
    void SetUpMatrix();
    bool CompareIdToColor(unsigned char r, unsigned char g, unsigned char b);

};

Model* ConstructCubeM();
Model* ConstructSphereM();
Model* ConstructPyramidM();
Model* ConstructSurfaceM();
Model* ConstructSkyboxM();
Model* LoadObjM(const char* filepath);
Model* AssembleModel();