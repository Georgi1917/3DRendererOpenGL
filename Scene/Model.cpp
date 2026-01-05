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

Model* ConstructCubeM()
{

    std::vector<Vertex> vertices = {
        
        {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
        {{ 0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
        {{ 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
        {{-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},

        
        {{ 0.5f, -0.5f, -0.5f}, {0.0f, 0.0f,-1.0f}, {0.0f, 0.0f}},
        {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f,-1.0f}, {1.0f, 0.0f}},
        {{-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f,-1.0f}, {1.0f, 1.0f}},
        {{ 0.5f,  0.5f, -0.5f}, {0.0f, 0.0f,-1.0f}, {0.0f, 1.0f}},

        
        {{-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        {{-0.5f, -0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
        {{-0.5f,  0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
        {{-0.5f,  0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},

        
        {{ 0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        {{ 0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
        {{ 0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
        {{ 0.5f,  0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},

        
        {{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
        {{ 0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
        {{ 0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
        {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},

        
        {{-0.5f, -0.5f, -0.5f}, {0.0f,-1.0f, 0.0f}, {0.0f, 0.0f}},
        {{ 0.5f, -0.5f, -0.5f}, {0.0f,-1.0f, 0.0f}, {1.0f, 0.0f}},
        {{ 0.5f, -0.5f,  0.5f}, {0.0f,-1.0f, 0.0f}, {1.0f, 1.0f}},
        {{-0.5f, -0.5f,  0.5f}, {0.0f,-1.0f, 0.0f}, {0.0f, 1.0f}},
    };

    std::vector<unsigned int> indices = {
        
        0, 1, 2,  2, 3, 0,
        
        4, 5, 6,  6, 7, 4,
        
        8, 9,10, 10,11, 8,
        
       12,13,14, 14,15,12,
        
       16,17,18, 18,19,16,
        
       20,21,22, 22,23,20
    };

    Material mat;
    Mesh* mesh = new Mesh(vertices, indices);

    mat.ambient = glm::vec3(1.0f, 0.5f, 0.31f);
    mat.diffuse = glm::vec3(1.0f, 0.5f, 0.31f);
    mat.specular = glm::vec3(0.5f, 0.5f, 0.5f);
    mat.shininess = 32.0f;
    mesh->material = mat;

    return new Model( {mesh} );

}

Model* ConstructSphereM()
{

    float radius = 1.0f;
    unsigned int stacks = 50;
    unsigned int sectors = 50;

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    for (unsigned int i = 0; i <= stacks; ++i)
    {

        float stackAngle = glm::pi<float>() / 2 - i * glm::pi<float>() / stacks;
        float xy = radius * cosf(stackAngle);
        float z = radius * sinf(stackAngle);

        for (unsigned int j = 0; j <= sectors; ++j)
        {

            float sectorAngle = j * 2 * glm::pi<float>() / sectors;

            float x = xy * cosf(sectorAngle);
            float y = xy * sinf(sectorAngle);

            glm::vec3 pos = glm::vec3(x, y, z);

            glm::vec3 normal = glm::normalize(glm::vec3(x, y, z));

            float u = (float)j / sectors;
            float v = (float)i / stacks;

            vertices.push_back(
                {{pos}, {normal}, {u, v}}
            );

        }

    }

    for (unsigned int i = 0; i < stacks; ++i)
    {

        unsigned int k1 = i * (sectors + 1);
        unsigned int k2 = k1 + sectors + 1;

        for (unsigned int j = 0; j < sectors; ++j, ++k1, ++k2)
        {

            if (i != 0)
            {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }

            if (i != (stacks - 1))
            {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }

        }

    }

    Material mat;
    Mesh* mesh = new Mesh(vertices, indices);

    mat.ambient = glm::vec3(1.0f, 0.5f, 0.31f);
    mat.diffuse = glm::vec3(1.0f, 0.5f, 0.31f);
    mat.specular = glm::vec3(0.5f, 0.5f, 0.5f);
    mat.shininess = 32.0f;
    mesh->material = mat;

    return new Model({ mesh });

}

Model* ConstructPyramidM()
{

    std::vector<Vertex> vertices = {
    
        {{-0.5f, 0.0f,  0.5f}, { 0.0f, -1.0f,  0.0f}, {0.0f, 0.0f}},
        {{-0.5f, 0.0f, -0.5f}, { 0.0f, -1.0f,  0.0f}, {0.0f, 5.0f}},
        {{ 0.5f, 0.0f, -0.5f}, { 0.0f, -1.0f,  0.0f}, {5.0f, 5.0f}},
        {{ 0.5f, 0.0f,  0.5f}, { 0.0f, -1.0f,  0.0f}, {5.0f, 0.0f}},

        {{-0.5f, 0.0f,  0.5f}, {-0.8f,  0.5f,  0.0f}, {0.0f, 0.0f}},
        {{-0.5f, 0.0f, -0.5f}, {-0.8f,  0.5f,  0.0f}, {5.0f, 0.0f}},
        {{ 0.0f, 0.8f,  0.0f}, {-0.8f,  0.5f,  0.0f}, {2.5f, 5.0f}},

        {{-0.5f, 0.0f, -0.5f}, { 0.0f,  0.5f, -0.8f}, {5.0f, 0.0f}},
        {{ 0.5f, 0.0f, -0.5f}, { 0.0f,  0.5f, -0.8f}, {0.0f, 0.0f}},
        {{ 0.0f, 0.8f,  0.0f}, { 0.0f,  0.5f, -0.8f}, {2.5f, 5.0f}},

        {{ 0.5f, 0.0f, -0.5f}, { 0.8f,  0.5f,  0.0f}, {0.0f, 0.0f}},
        {{ 0.5f, 0.0f,  0.5f}, { 0.8f,  0.5f,  0.0f}, {5.0f, 0.0f}},
        {{ 0.0f, 0.8f,  0.0f}, { 0.8f,  0.5f,  0.0f}, {2.5f, 5.0f}},

        {{ 0.5f, 0.0f,  0.5f}, { 0.0f,  0.5f,  0.8f}, {5.0f, 0.0f}},
        {{-0.5f, 0.0f,  0.5f}, { 0.0f,  0.5f,  0.8f}, {0.0f, 0.0f}},
        {{ 0.0f, 0.8f,  0.0f}, { 0.0f,  0.5f,  0.8f}, {2.5f, 5.0f}}

    };


    std::vector<unsigned int> indices = {
        0, 1, 2,
        0, 2, 3,
        4, 6, 5,
        7, 9, 8,
        10, 12, 11,
        13, 15, 14
    };

    Material mat;
    Mesh* mesh = new Mesh(vertices, indices);

    mat.ambient = glm::vec3(1.0f, 0.5f, 0.31f);
    mat.diffuse = glm::vec3(1.0f, 0.5f, 0.31f);
    mat.specular = glm::vec3(0.5f, 0.5f, 0.5f);
    mat.shininess = 32.0f;
    mesh->material = mat;

    return new Model( {mesh} );

}

Model* ConstructSurfaceM()
{

    std::vector<Vertex> vertices = {
        {{0.5f,  0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},  
        {{0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},  
        {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
        {{-0.5f,  0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},

        {{0.5f,  0.5f, 0.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}},  
        {{0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}},  
        {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}},
        {{-0.5f,  0.5f, 0.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}},

    };

    std::vector<unsigned int> indices = {
        0, 1, 2,
        2, 3, 0,

        6, 5, 4,
        4, 7, 6,
    };

    Mesh* mesh = new Mesh(vertices, indices);

    return new Model( {mesh} );

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

    return new Model( {mesh} );

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