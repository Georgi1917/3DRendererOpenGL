#pragma once
#define GLEW_STATIC
#include "include/glew.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "BufferLayoutObject.h"

class Renderable
{

    private:
        VertexArray vao;
        VertexBuffer vbo;
        IndexBuffer ibo;

    public:

        VertexArray GetVao();

};