#pragma once

#include "VertexBuffer.h"
#include "BufferLayoutObject.h"

class VertexArray
{

    private:
        unsigned int rendererID;

    public:
        VertexArray();
        ~VertexArray();

        void AddBuffer(VertexBuffer& vbo, BufferLayoutObject& layout);
        void Bind();
        void Unbind();

};