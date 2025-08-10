#pragma once
#include "Renderable.h"

class Cube : public Renderable
{
    private:

        unsigned int numOfVertices = 36;
        float positions[216] = {
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
        0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
        0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,

        0.5f,  0.5f,  0.5f,  0.29f, 0.6f, 0.57f,
        0.5f,  0.5f, -0.5f,  0.29f, 0.6f, 0.57f,
        0.5f, -0.5f, -0.5f,  0.29f, 0.6f, 0.57f,
        0.5f, -0.5f, -0.5f,  0.29f, 0.6f, 0.57f,
        0.5f, -0.5f,  0.5f,  0.29f, 0.6f, 0.57f,
        0.5f,  0.5f,  0.5f,  0.29f, 0.6f, 0.57f,

        -0.5f, -0.5f, -0.5f, 1.0f, 0.6f, 0.12f, 
        0.5f, -0.5f, -0.5f,  1.0f, 0.6f, 0.12f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.6f, 0.12f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.6f, 0.12f,
        -0.5f, -0.5f,  0.5f, 1.0f, 0.6f, 0.12f,
        -0.5f, -0.5f, -0.5f, 1.0f, 0.6f, 0.12f,

        -0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 
        -0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 1.0f
        };

        VertexArray cubeVAO;
        VertexBuffer cubeVBO;
        BufferLayoutObject cubeLayout;

    public:
        Cube(unsigned int _id);
        ~Cube();
        float *GetData();

};