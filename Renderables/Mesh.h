#pragma once
#define GLEW_STATIC
#include "../include/glew.h"
#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "../include/glm/gtc/type_ptr.hpp"
#include "../include/tiny_obj_loader.h"
#include "../VertexArray.h"
#include "../VertexBuffer.h"
#include "../IndexBuffer.h"
#include "../BufferLayoutObject.h"
#include "../Textures/Texture.h"
#include <vector>

struct Vertex
{

    glm::vec3 points;
    glm::vec3 normals;
    glm::vec2 texCoords;

};

struct Mesh
{

    unsigned int id;
    Texture *tex = nullptr;

    VertexArray        vao = VertexArray();
    VertexBuffer       vbo = VertexBuffer();
    IndexBuffer        ibo = IndexBuffer();
    BufferLayoutObject layout = BufferLayoutObject();

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    glm::vec3 color = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::vec3 pickingColor;

    glm::mat4 model = glm::mat4(1.0f);
    glm::vec3 trans = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);

    void Init(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
    void Draw();
    void SetUpMatrix();
    bool CompareIdToColor(unsigned char r, unsigned char g, unsigned char b);

};

Mesh* ConstructCube();
Mesh* ConstructSphere();
Mesh* ConstructPyramid();
Mesh* LoadObj(const char* filepath);