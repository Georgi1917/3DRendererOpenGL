#pragma once

class VertexBuffer
{
    private:
        unsigned int rendererID;
    public:
        VertexBuffer(const void* data, unsigned int size);
        VertexBuffer();
        ~VertexBuffer();

        void Bind();
        void Unbind();
};