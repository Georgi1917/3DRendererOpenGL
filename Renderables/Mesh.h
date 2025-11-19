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
#include "../Shader.h"
#include <vector>

struct Vertex
{

    glm::vec3 points;
    glm::vec3 normals;
    glm::vec2 texCoords;

};

struct Material
{

    std::string name;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    std::string ambientTexName;
    std::string diffuseTexName;
    std::string specularTexName;

    float shininess;

};

struct Mesh
{

    unsigned int id;

    VertexArray        vao = VertexArray();
    VertexBuffer       vbo = VertexBuffer();
    IndexBuffer        ibo = IndexBuffer();
    BufferLayoutObject layout = BufferLayoutObject();

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    Material material;

    glm::vec3 color = glm::vec3(0.5f, 0.5f, 0.5f);

    void Init(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
    void Draw(Shader &shader);

};