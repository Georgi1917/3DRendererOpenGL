#include "Mesh.h"
#include <iostream>

unsigned int currId = 1;
glm::vec3 currTrans = glm::vec3(0.0f, 0.0f, 0.0f);

void Mesh::Init(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
{

    this->vertices = vertices;
    this->indices  = indices;

    id = currId;
    currId++;

    vao.Bind();
    vbo.init(vertices.data(), vertices.size() * sizeof(Vertex));
    ibo.init(indices.data(), indices.size());
    layout.Push<float>(3);
    layout.Push<float>(3);
    layout.Push<float>(2);
    vao.AddBuffer(vbo, layout);
    vao.Unbind();

}

void Mesh::Draw(Shader &shader)
{

    vao.Bind();
    ibo.Bind();
    glDrawElements(GL_TRIANGLES, ibo.Count(), GL_UNSIGNED_INT, 0);
    vao.Unbind();
    ibo.Unbind();

}

Mesh::~Mesh()
{

    for (auto tex : textures)
    {

        delete tex;

    }

}
