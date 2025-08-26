#pragma once
#include "Renderable.h"

class LightSource : public Renderable
{

    private:

        unsigned int numOfVertices = 36;
        float positions[216] = {
        -0.5f, -0.5f, -0.5f, 0.0f,  0.0f, -1.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f, 0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f, 0.0f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f, 0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, 0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

        0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  0.0f,
        0.5f,  0.5f, -0.5f, 1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,
        0.5f, -0.5f,  0.5f, 1.0f,  0.0f,  0.0f,
        0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, 0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f
        };

        VertexArray lightVAO;
        VertexBuffer lightVBO;
        BufferLayoutObject layout;

    public:
        LightSource();
        ~LightSource();

        unsigned int GetNumberOfVertices();
        VertexArray& GetVAO();
        std::string GetClassName() override;

};