#pragma once
#define GLEW_STATIC
#include "../include/glew.h"
#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "../include/glm/gtc/type_ptr.hpp"
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
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    glm::vec3 color = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::vec3 pickingColor;

    glm::mat4 model = glm::mat4(1.0f);
    glm::vec3 trans = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);

    void Init(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices);

};