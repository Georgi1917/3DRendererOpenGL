#pragma once
#include "Mesh.h"
#include "../Textures/Texture.h"
#include "../Shader.h"
#include "../include/assimp/Importer.hpp"
#include "../include/assimp/scene.h"
#include "../include/assimp/postprocess.h"

struct Model
{

    unsigned int id;

    std::vector<Mesh*> modelMeshes;
    std::vector<Texture*> loadedTextures;

    glm::mat4 model = glm::mat4(1.0f);
    glm::vec3 trans = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);

    glm::vec3 pickingColor;

    Model(std::vector<Mesh*> meshes);
    Model(const char* filepath);
    ~Model();
    
    void Draw(Shader &shader);
    void SetUpMatrix();
    bool CompareIdToColor(unsigned char r, unsigned char g, unsigned char b);

    void LoadModel(const char* filepath);
    void ProccessNode(aiNode *node, const aiScene *scene);
    Mesh* ProccessMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture*> LoadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
    Material LoadMaterial(aiMaterial *mat);
    void OrderMeshesByMaterial(const aiScene *scene);

};

Model* ConstructCubeM();
Model* ConstructSphereM();
Model* ConstructPyramidM();
Model* ConstructSurfaceM();
Model* ConstructSkyboxM();
Model* LoadObjM(const char* filepath);
Model* AssembleModel(std::vector<Mesh*> &meshes, std::vector<tinyobj::material_t> materials);