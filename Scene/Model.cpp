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

Model* AssembleModel(std::vector<Mesh*> &meshes, std::vector<tinyobj::material_t> materials)
{

    std::vector<Mesh*> newMeshes;

    for (auto it = materials.begin(); it != materials.end(); it++)
    {

        std::string matName = it->name;
        std::vector<Vertex> newVertices;
        std::vector<unsigned int> newIndices;

        for (auto mesh : meshes)
        {

            if (mesh->material.name == matName)
            {

                unsigned int idxOffset = newIndices.size();

                newVertices.insert(newVertices.end(), mesh->vertices.begin(), mesh->vertices.end());

                for (unsigned int i : mesh->indices)
                {

                    newIndices.push_back(i + idxOffset);

                }

            }   

        }

        if (newVertices.empty() || newIndices.empty())
            continue;

        Material mat;
        Mesh *mesh = new Mesh(newVertices, newIndices);

        mat.name = it->name;
        mat.ambient = glm::vec3(it->ambient[0], it->ambient[1], it->ambient[2]);
        mat.diffuse = glm::vec3(it->diffuse[0], it->diffuse[1], it->diffuse[2]);
        mat.specular = glm::vec3(it->specular[0], it->specular[1], it->specular[2]);
        mat.shininess = it->shininess;

        mesh->material = mat;

        if (it->ambient_texname != "")
        {
            mesh->textures.push_back(new Texture(("obj-files/" + it->ambient_texname).c_str(), "AmbientTexture"));
            std::cout << "ambient : " << it->ambient_texname << "\n";
        }
        if (it->diffuse_texname != "")
        {
            mesh->textures.push_back(new Texture(("obj-files/" + it->diffuse_texname).c_str(), "DiffuseTexture"));
            std::cout << "diffuse : " << it->diffuse_texname << "\n";
        }
        if (it->specular_texname != "")
        {
            mesh->textures.push_back(new Texture(("obj-files/" + it->specular_texname).c_str(), "SpecularTexture"));
            std::cout << "specular : " << it->specular_texname << "\n";
        }

        newMeshes.push_back(mesh);

    }

    for (auto mesh: meshes)
        delete mesh;

    return new Model(newMeshes);

}

Model* LoadObjM(const char* filepath)
{

    tinyobj::ObjReaderConfig readerConfig;
    readerConfig.mtl_search_path = "obj-files/";
    tinyobj::ObjReader reader;

    if (!reader.ParseFromFile(filepath, readerConfig))
    {

        if (!reader.Error().empty())
            std::cout << "TinyObjLoader" << reader.Error() << "\n";

        exit(1);
    }

    if (!reader.Warning().empty())
        std::cout << "TinyObjLoader Warning : " << reader.Warning() << "\n";

    const tinyobj::attrib_t attrib = reader.GetAttrib();
    std::vector<tinyobj::shape_t> shapes = reader.GetShapes();
    std::vector<tinyobj::material_t> materials = reader.GetMaterials();

    std::vector<Mesh*> meshes;

    for (const auto& shape : shapes)
    {

        unsigned int indexOffset = 0;

        for (unsigned int f = 0; f < shape.mesh.num_face_vertices.size(); f++)
        {

            unsigned int fv = shape.mesh.num_face_vertices[f];        
            std::vector<Vertex> vertices;
            std::vector<unsigned int > indices;

            for (unsigned int v = 0; v < fv; v++)
            {

                tinyobj::index_t idx = shape.mesh.indices[indexOffset + v];

                Vertex vertex;

                float vx = attrib.vertices[3 * idx.vertex_index + 0];
                float vy = attrib.vertices[3 * idx.vertex_index + 1];
                float vz = attrib.vertices[3 * idx.vertex_index + 2];

                float nx = 0, ny = 0, nz = 0;
                if (idx.normal_index >= 0)
                {

                    nx = attrib.normals[3 * idx.normal_index + 0];
                    ny = attrib.normals[3 * idx.normal_index + 1];
                    nz = attrib.normals[3 * idx.normal_index + 2];

                }

                float tv = 0, tu = 0;
                if (idx.texcoord_index >= 0)
                {

                    tv = attrib.texcoords[2 * idx.texcoord_index + 0];
                    tu = attrib.texcoords[2 * idx.texcoord_index + 1];

                }

                vertex.points = glm::vec3(vx, vy, vz);
                vertex.normals = glm::vec3(nx, ny, nz);
                vertex.texCoords = glm::vec2(tv, tu);

                vertices.push_back(vertex);
                indices.push_back(indices.size());

            }

            Material mat;
            Mesh *mesh = new Mesh(vertices, indices);

            if (shape.mesh.material_ids[f] >= 0)
            {
                tinyobj::material_t currMat = materials[shape.mesh.material_ids[f]];
                mat.name = currMat.name;
                mat.ambient = glm::vec3(currMat.ambient[0], currMat.ambient[1], currMat.ambient[2]);
                mat.diffuse = glm::vec3(currMat.diffuse[0], currMat.diffuse[1], currMat.diffuse[2]);
                mat.specular = glm::vec3(currMat.specular[0], currMat.specular[1], currMat.specular[2]);
                mat.shininess = currMat.shininess;
                mesh->material = mat;
            }

            meshes.push_back(mesh);

            indexOffset += fv;
        
        }

    }

    return AssembleModel(meshes, materials);

}

