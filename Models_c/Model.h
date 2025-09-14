#pragma once
#include "Mesh.h"
#include "../include/assimp/Importer.hpp"
#include "../include/assimp/scene.h"
#include "../include/assimp/postprocess.h"
#include "../include/stb_image.h"

class Model
{

    public:
        Model(const char *path);
        void Draw(Shader &shader);
        glm::mat4 modelMat;
        glm::vec3 translation;
        glm::vec3 rotation;
        glm::vec3 scale;
        void ResetModelMat();

    private:
        std::vector<Mesh> meshes;
        std::string dir;

        void LoadModel(std::string path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<Texture_c> loadMaterialTexture(aiMaterial *mat, aiTextureType type, std::string typeName);
        unsigned int TextureFromFile(const char *path);

};