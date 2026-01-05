#pragma once

class VertexBuffer
{
    private:
        unsigned int rendererID;
    public:
        void init(const void* data, unsigned int size);
        VertexBuffer();
        ~VertexBuffer();

        void Bind();
        void Unbind();
};