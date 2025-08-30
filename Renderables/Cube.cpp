#include "Cube.h"

Cube::Cube(glm::vec3 _color) : Renderable(_color), cubeVAO(), cubeVBO(), cubeLayout()
{

    cubeVAO.Bind();
    cubeVBO.init(positions, sizeof(positions));
    cubeLayout.Push<float>(3);
    cubeLayout.Push<float>(3);
    cubeLayout.Push<float>(2);
    cubeVAO.AddBuffer(cubeVBO, cubeLayout);
    cubeVAO.Unbind();

}

Cube::Cube(glm::vec3 _color, Texture *t) : Renderable(_color, t), cubeVAO(), cubeVBO(), cubeLayout()
{

    cubeVAO.Bind();
    cubeVBO.init(positions, sizeof(positions));
    cubeLayout.Push<float>(3);
    cubeLayout.Push<float>(3);
    cubeLayout.Push<float>(2);
    cubeVAO.AddBuffer(cubeVBO, cubeLayout);
    cubeVAO.Unbind();

}

Cube::~Cube()
{

}

VertexArray& Cube::GetVAO()
{

    return cubeVAO;

}

unsigned int Cube::GetNumberOfVertices()
{
    return numOfVertices;
}

std::string Cube::GetClassName()
{

    return "Cube";

}

void Cube::Draw()
{

    //tex->Bind();
    cubeVAO.Bind();
    glDrawArrays(GL_TRIANGLES, 0, numOfVertices);
    cubeVAO.Unbind();
    //tex->Unbind();

}