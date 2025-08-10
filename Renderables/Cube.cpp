#include "Cube.h"

Cube::Cube(unsigned int _id) : Renderable(_id)
{

    cubeVAO = VertexArray();
    cubeVBO = VertexBuffer(positions, sizeof(positions));
    BufferLayoutObject layout;
    layout.Push<float>(3);
    layout.Push<float>(3);
    cubeVAO.AddBuffer(cubeVBO, layout);
    cubeVAO.Unbind();

}

Cube::~Cube()
{

}

float *Cube::GetData()
{

    return positions;

}