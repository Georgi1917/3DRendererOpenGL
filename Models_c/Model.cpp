#include "Model.h"
#include <iostream>

Model::Model(const char *path)
{

    LoadModel(path);
    modelMat = glm::mat4(1.0f);
    translation = glm::vec3(-2.0f, 0.0f, 0.0f);
    modelMat = glm::translate(modelMat, translation);
    rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    modelMat = glm::rotate(modelMat, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    modelMat = glm::rotate(modelMat, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    modelMat = glm::rotate(modelMat, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    scale = glm::vec3(1.0f, 1.0f, 1.0f);
    modelMat = glm::scale(modelMat, scale);

}

void Model::LoadModel(std::string path)
{

    Assimp::Importer importer;

    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {

        std::cout << "ERROR : ASSIMP : " << importer.GetErrorString() << "\n";
        return;

    }

    dir = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);

}

void Model::processNode(aiNode *node, const aiScene *scene)
{

    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {

        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));

    }

    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {

        processNode(node->mChildren[i], scene);

    }

}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
{

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture_c> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {

        Vertex vertex;
        vertex.pos = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
        vertex.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);

        if (mesh->mTextureCoords[0])
        {

            vertex.texCoords = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);

        }
        else 
            vertex.texCoords = glm::vec2(0.0f, 0.0f);
        
        vertices.push_back(vertex);

    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {

        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);

    }

    if (mesh->mMaterialIndex >= 0)
    {

        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        std::vector<Texture_c> diffuse = loadMaterialTexture(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuse.begin(), diffuse.end());

        std::vector<Texture_c> specular = loadMaterialTexture(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specular.begin(), specular.end());

    }

    return Mesh(vertices, indices, textures);

}

std::vector<Texture_c> Model::loadMaterialTexture(aiMaterial *mat, aiTextureType type, std::string typeName)
{

    std::vector<Texture_c> textures;
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {

        aiString str;
        mat->GetTexture(type, i, &str);
        Texture_c texture;
        texture.id = TextureFromFile(str.C_Str());
        texture.type = typeName;
        textures.push_back(texture);

    }

    return textures;

}

unsigned int Model::TextureFromFile(const char *path)
{

    std::string filename = std::string(path);
    filename = dir + '/' + filename;

    unsigned int textureId;
    glGenTextures(1, &textureId);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {

        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureId);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);

    }
    else 
    {

        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);

    }

    return textureId;

}

void Model::Draw(Shader &shader)
{

    for (unsigned int i = 0; i < meshes.size(); i++)
    {

        meshes[i].Draw(shader);

    }

}

void Model::ResetModelMat()
{

    modelMat = glm::mat4(1.0f);
    modelMat = glm::translate(modelMat, translation);
    modelMat = glm::rotate(modelMat, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    modelMat = glm::rotate(modelMat, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    modelMat = glm::rotate(modelMat, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    modelMat = glm::scale(modelMat, scale);

}