#include "Mesh.h"
#include <iostream>

unsigned int currId = 1;
glm::vec3 currTrans = glm::vec3(0.0f, 0.0f, 0.0f);

void Mesh::SetUpMatrix()
{

    model = glm::translate(model, trans);
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, scale);

}

void Mesh::Init(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
{

    this->vertices = vertices;
    this->indices  = indices;

    id = currId;
    currId++;
    trans = currTrans;
    currTrans.x += 2.0f;

    vao.Bind();
    vbo.init(vertices.data(), vertices.size() * sizeof(Vertex));
    ibo.init(indices.data(), indices.size());
    layout.Push<float>(3);
    layout.Push<float>(3);
    layout.Push<float>(2);
    vao.AddBuffer(vbo, layout);
    vao.Unbind();

    SetUpMatrix();

    pickingColor = glm::vec3(
        (id & 0x000000FF) / 255.0f,
        ((id & 0x0000FF00) >> 8) / 255.0f,
        ((id & 0x00FF0000) >> 16) / 255.0f
    );

}

void Mesh::Draw()
{

    vao.Bind();
    ibo.Bind();
    glDrawElements(GL_TRIANGLES, ibo.Count(), GL_UNSIGNED_INT, 0);
    vao.Unbind();
    ibo.Unbind();

}

bool Mesh::CompareIdToColor(unsigned char r, unsigned char g, unsigned char b)
{

    unsigned int id = r + (g << 8) + (b << 16);

    return id == this->id;

}

Mesh* ConstructCube()
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

    return mesh;

}

Mesh* ConstructSphere()
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

    return mesh;

}

Mesh* ConstructPyramid()
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
    return mesh;

}

Mesh* LoadObj(const char* filepath)
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

    std::vector<Vertex> vertices;
    std::vector<unsigned int > indices;

    for (const auto& shape : shapes)
    {

        unsigned int indexOffset = 0;

        for (unsigned int f = 0; f < shape.mesh.num_face_vertices.size(); f++)
        {

            unsigned int fv = shape.mesh.num_face_vertices[f];

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

            indexOffset += fv;

        }

    }

    Mesh* mesh = new Mesh();
    mesh->Init(vertices, indices);

    return mesh;

}