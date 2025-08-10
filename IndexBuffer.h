#pragma once

class IndexBuffer
{
    private:
        unsigned int rendererID;
        unsigned int countOfIndeces;
    public:
        IndexBuffer(const unsigned int* data, unsigned int count);
        IndexBuffer();
        ~IndexBuffer();

        void Bind();
        void Unbind();

        unsigned int Count() { return countOfIndeces; }
};