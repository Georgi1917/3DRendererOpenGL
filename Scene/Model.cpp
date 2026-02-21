#include "Model.h"
#include <iostream>

unsigned int currIdM = 1;
glm::vec3 currTransM = glm::vec3(0.0f, 0.0f, 0.0f);

Model::Model(std::vector<Mesh*> meshes)
{

    id = currIdM;
    currIdM++;

    modelMeshes = meshes;
    trans = currTransM;
    currTransM.x += 2.0f;

    pickingColor = glm::vec3(
        (id & 0x000000FF) / 255.0f,
        ((id & 0x0000FF00) >> 8) / 255.0f,
        ((id & 0x00FF0000) >> 16) / 255.0f
    );

}

Model::Model(const char* filepath)
{

    id = currIdM;
    currIdM++;

    trans = currTransM;
    currTransM.x += 2.0f;

    pickingColor = glm::vec3(
        (id & 0x000000FF) / 255.0f,
        ((id & 0x0000FF00) >> 8) / 255.0f,
        ((id & 0x00FF0000) >> 16) / 255.0f
    );

    LoadModel(filepath);

}

Model::~Model()
{

    for (auto m : modelMeshes)
    {

        delete m;

    }

}

void Model::Draw(Shader& shader)
{

    for (auto& mesh : modelMeshes)
    {

        shader.SetVec3f("material.ambient", mesh->material.ambient);
        shader.SetVec3f("material.diffuse", mesh->material.diffuse);
        shader.SetVec3f("material.specular", mesh->material.specular);
        shader.Set1F("material.shininess", mesh->material.shininess);

        shader.SetBool("material.hasAmbientTexture", false);
        shader.SetBool("material.hasDiffuseTexture", false);
        shader.SetBool("material.hasSpecularTexture", false);
        
        for (int i = 0; i < mesh->textures.size(); i++)
        {

            shader.SetBool("material.has" + mesh->textures[i]->textureType, true);
            shader.Set1I("material." + mesh->textures[i]->textureType, i);
            glActiveTexture(GL_TEXTURE0 + i);
            mesh->textures[i]->Bind();

        }

        mesh->Draw(shader);

        glActiveTexture(GL_TEXTURE0);

    }

}

void Model::SetUpMatrix()
{

    model = glm::translate(model, trans);
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, scale);

}

bool Model::CompareIdToColor(unsigned char r, unsigned char g, unsigned char b)
{

    unsigned int id = r + (g << 8) + (b << 16);

    return id == this->id;

}

void Model::LoadModel(const char* filepath)
{

    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(filepath, aiProcess_Triangulate | aiProcess_FlipUVs);	
	
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }
    
    ProccessNode(scene->mRootNode, scene);
    OrderMeshesByMaterial(scene);

}

void Model::ProccessNode(aiNode *node, const aiScene *scene)
{

    for (int i = 0; i < node->mNumMeshes; i++)
    {

        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        modelMeshes.push_back(ProccessMesh(mesh, scene));

    }

    for (int i = 0; i < node->mNumChildren; i++)
    {

        ProccessNode(node->mChildren[i], scene);

    }

}

std::vector<Texture*> Model::LoadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName)
{

    std::vector<Texture*> textures;
    bool skip = false;
    for (int i = 0; i < mat->GetTextureCount(type); i++)
    {

        bool skip = false;
        aiString texPath("obj-files/");
        aiString path;
        mat->GetTexture(type, i, &path);
        texPath.Append(path.C_Str());

        for (int j = 0; j < loadedTextures.size(); j++)
        {

            if (std::strcmp(loadedTextures[j]->loc.c_str(), path.C_Str()) == 0)
            {

                textures.push_back(loadedTextures[j]);
                skip = true;
                break;

            }

        }

        if (!skip)
        {

            Texture *texture = new Texture(texPath.C_Str(), typeName);
            textures.push_back(texture);
            loadedTextures.push_back(texture);

        }

    }

    return textures;

}

Material Model::LoadMaterial(aiMaterial *mat)
{

    Material material;

    aiColor3D color(0.0f);
    float shinniness;

    material.name = mat->GetName().C_Str();

    mat->Get(AI_MATKEY_COLOR_AMBIENT, color);
    material.ambient = glm::vec3(color.r, color.g, color.b);

    mat->Get(AI_MATKEY_COLOR_DIFFUSE, color);
    material.diffuse = glm::vec3(color.r, color.g, color.b);

    mat->Get(AI_MATKEY_COLOR_SPECULAR, color);
    material.specular = glm::vec3(color.r, color.g, color.b);

    mat->Get(AI_MATKEY_SHININESS, shinniness);
    material.shininess = shinniness;

    return material;

}

void Model::OrderMeshesByMaterial(const aiScene *scene)
{

    std::cout << "Mesh Number : " << scene->mNumMeshes << "\n";
    std::cout << "Mat number : " << scene->mNumMaterials << "\n";

    std::vector<Mesh*> newMeshes;

    for (int i = 0; i < scene->mNumMaterials; i++)
    {

        std::cout << "Mat Name : " << scene->mMaterials[i]->GetName().C_Str() << "\n";
        std::vector<Vertex> newVertices;
        std::vector<unsigned int> newIndices;
        std::vector<Texture*> newTextures;

        for (Mesh* mesh: modelMeshes)
        {

            if (mesh->material.name != scene->mMaterials[i]->GetName().C_Str())
                continue;

            unsigned int idxOffset = newIndices.size();
            newVertices.insert(newVertices.end(), mesh->vertices.begin(), mesh->vertices.end());
            
            for (unsigned int i : mesh->indices)
            {

                newIndices.push_back(i + idxOffset);

            }

        }

        if (newVertices.empty() || newIndices.empty())
            continue;

        Mesh* mesh = new Mesh(newVertices, newIndices);
        mesh->material = LoadMaterial(scene->mMaterials[i]);

        std::vector<Texture*> ambientTextures = LoadMaterialTextures(scene->mMaterials[i], aiTextureType_AMBIENT, "AmbientTexture");
        std::vector<Texture*> diffuseTextures = LoadMaterialTextures(scene->mMaterials[i], aiTextureType_DIFFUSE, "DiffuseTexture");
        std::vector<Texture*> specularTextures = LoadMaterialTextures(scene->mMaterials[i], aiTextureType_SPECULAR, "SpecularTexture");

        newTextures.insert(newTextures.end(), ambientTextures.begin(), ambientTextures.end());
        newTextures.insert(newTextures.end(), diffuseTextures.begin(), diffuseTextures.end());
        newTextures.insert(newTextures.end(), specularTextures.begin(), specularTextures.end());

        mesh->textures = std::move(newTextures);

        newMeshes.push_back(mesh);

    }

    for (auto it = modelMeshes.begin(); it != modelMeshes.end();)
    {

        delete (*it);
        it = modelMeshes.erase(it);

    }

    modelMeshes = std::move(newMeshes);

    std::cout << "New number of Meshes : " << modelMeshes.size() << "\n";

}

Mesh* Model::ProccessMesh(aiMesh *mesh, const aiScene *scene)
{

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    Material mat;

    for (int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        vertex.points = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
        vertex.normals = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);

        if (mesh->mTextureCoords[0])
        {

            vertex.texCoords = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);

        }
        else vertex.texCoords = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertex);

    }

    for (int i = 0; i < mesh->mNumFaces; i++)
    {

        aiFace face = mesh->mFaces[i];

        for (int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);

    }

    if (mesh->mMaterialIndex >= 0)
    {

        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

        mat = LoadMaterial(material);

    }

    Mesh* m = new Mesh(vertices, indices);
    m->material = mat;

    return m;

}

Model* ConstructSkyboxM()
{

    std::vector<Vertex> skyboxVertices = {
        {{-1.0f, -1.0f,  1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        {{1.0f, -1.0f,  1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        {{1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        {{-1.0f,  1.0f,  1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        {{1.0f,  1.0f,  1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        {{1.0f,  1.0f, -1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        {{-1.0f,  1.0f, -1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}}
    };

    std::vector<unsigned int> skyboxIndices = {
        // Back face (-Z)
        1, 2, 6,
        6, 5, 1,
        // Left
        0, 4, 7,
        7, 3, 0,
        // Top
        4, 5, 6,
        6, 7, 4,
        // Bottom
        0, 3, 2,
        2, 1, 0,
        // Back
        0, 1, 5,
        5, 4, 0,
        // Front
        3, 7, 6,
        6, 2, 3
    };

    Mesh* mesh = new Mesh(skyboxVertices, skyboxIndices);

    currTransM.x -= 2.0f;
    return new Model( {mesh} );

}

