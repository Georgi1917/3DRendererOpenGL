#pragma once
#define GLEW_STATIC
#include "../include/glew.h"
#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "../include/glm/gtc/type_ptr.hpp"
#include "../include/tiny_obj_loader.h"
#include "../Renderer/VertexArray.h"
#include "../Renderer/VertexBuffer.h"
#include "../Renderer/IndexBuffer.h"
#include "../Renderer/BufferLayoutObject.h"
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

    float shininess;

};

struct Mesh
{

    unsigned int id;

    VertexArray        vao = VertexArray();
    IndexBuffer        ibo = IndexBuffer();

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    Material material;
    std::vector<Texture*> textures;

    void Draw(Shader &shader);
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
    ~Mesh();

};