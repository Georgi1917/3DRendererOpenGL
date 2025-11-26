#pragma once
#include "Mesh.h"
#include "../Textures/Texture.h"
#include "../Shader.h"

struct Model
{

    unsigned int id;

    std::vector<Mesh*> modelMeshes;

    glm::mat4 model = glm::mat4(1.0f);
    glm::vec3 trans = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);

    glm::vec3 pickingColor;
    bool uvFlipped = false;

    Model(std::vector<Mesh*> meshes);
    ~Model();
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
Model* AssembleModel(std::vector<Mesh*> &meshes, std::vector<tinyobj::material_t> materials);