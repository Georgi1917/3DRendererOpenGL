#include "Mesh.h"

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