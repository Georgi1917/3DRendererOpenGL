#pragma once
#define GLEW_STATIC
#include "include/glew.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Renderables/Renderable.h"


class Renderer
{
    public:
        void DrawArrays(VertexArray& vao, unsigned int mode, unsigned int first, unsigned int indicesCount);
        void DrawElements(VertexArray& vao, IndexBuffer& ibo, unsigned int mode, unsigned int type);
        void Clear();
        void EnableDepthTesting();
};