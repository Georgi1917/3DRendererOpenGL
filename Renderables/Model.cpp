#include "Model.h"
#include <iostream>

unsigned int currIdM = 1;
glm::vec3 currTransM = glm::vec3(0.0f, 0.0f, 0.0f);

Model::Model(std::vector<Mesh*> meshes)
{

    modelMeshes = meshes;
    trans = currTransM;
    currTransM.x += 2.0f;

}

void Model::Draw(Shader& shader)
{

    for (auto& mesh : modelMeshes)
    {

        mesh->Draw(shader);

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

    Mesh* mesh = new Mesh();
    mesh->Init(vertices, indices);

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

    Mesh* mesh = new Mesh();
    mesh->Init(vertices, indices);

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

    Mesh* mesh = new Mesh();
    mesh->Init(vertices, indices);

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

    Mesh* mesh = new Mesh();
    mesh->Init(vertices, indices);
    mesh->rotation.x = -90.0f;
    mesh->trans = glm::vec3(3.8f, -1.4f, 0.0f);
    mesh->scale = glm::vec3(6.0f, 6.0f, 6.0f);
    mesh->SetUpMatrix();
    currTransM.x -= 2.0f;

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

    Mesh* mesh = new Mesh();
    mesh->Init(skyboxVertices, skyboxIndices);

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

            Mesh *mesh = new Mesh();
            mesh->Init(vertices, indices);
            meshes.push_back(mesh);

            indexOffset += fv;
        
        }

    }

    // for (const auto& mat : materials)
    // {

    //     std::cout << "----------------------" << "\n";
    //     std::cout << mat.name << "\n";
    //     std::cout << mat.ambient[0] << " " << mat.ambient[1] << " " << mat.ambient[2] << "\n";
    //     std::cout << mat.diffuse[0] << " " << mat.diffuse[1] << " " << mat.diffuse[2] << "\n";
    //     std::cout << mat.specular[0] << " " << mat.specular[1] << " " << mat.specular[2] << "\n";
    //     std::cout << "----------------------" << "\n";

    // }

    // Mesh* mesh = new Mesh();
    // mesh->Init(vertices, indices);

    //return mesh;

    return new Model(meshes);

}