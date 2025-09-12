#pragma once
#define GLEW_STATIC

#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "../include/glm/gtc/type_ptr.hpp"
#include "../Shader.h"
#include "../include/glew.h"
#include <string>
#include <vector>

struct Vertex
{

    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec2 texCoords;

};

struct Texture_c
{

    unsigned int id;
    std::string type;

};

class Mesh
{

    public:
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture_c> textures;

        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture_c> textures);
        void Draw(Shader &shader);

    private:
        unsigned int VAO, VBO, IBO;

        void setUpMesh();

};