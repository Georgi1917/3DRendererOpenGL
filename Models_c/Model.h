#pragma once
#include "Mesh.h"
#include "../include/assimp/Importer.hpp"
#include "../include/assimp/scene.h"
#include "../include/assimp/postprocess.h"

class Model
{

    public:
        Model(char *path);
        void Draw(Shader &shader);

    private:
        std::vector<Mesh> meshes;
        std::string dir;

        void LoadModel(std::string path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<Texture_c> loadMaterialTexture(aiMaterial *mat, aiTextureType type, std::string typeName);

};