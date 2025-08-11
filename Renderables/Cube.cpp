#include "Cube.h"

Cube::Cube(unsigned int _id) : Renderable(_id), cubeVAO(), cubeVBO(), cubeLayout()
{

    cubeVAO.Bind();
    cubeVBO.init(positions, sizeof(positions));
    cubeLayout.Push<float>(3);
    cubeLayout.Push<float>(3);
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