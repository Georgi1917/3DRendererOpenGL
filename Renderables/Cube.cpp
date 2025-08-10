#include "Cube.h"

Cube::Cube(unsigned int _id) : Renderable(_id)
{

    cubeVAO = VertexArray();
    cubeVBO = VertexBuffer(positions, sizeof(positions));
    cubeLayout.Push<float>(3);
    cubeLayout.Push<float>(3);
    cubeVAO.AddBuffer(cubeVBO, cubeLayout);
    cubeVAO.Unbind();

}

Cube::~Cube()
{

}

float *Cube::GetData()
{

    return positions;

}

VertexArray Cube::GetVAO()
{

    return cubeVAO;

}