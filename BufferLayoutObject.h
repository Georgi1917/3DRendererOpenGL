#pragma once
#define GLEW_STATIC
#include "include/glew.h"
#include <vector>

struct LayoutElement
{

    unsigned int index;
    unsigned int count;
    unsigned int type;
    bool normalized;

    unsigned int GetType()
    {

        switch(type)
        {
            case GL_FLOAT: return sizeof(float);
            case GL_UNSIGNED_INT: return sizeof(unsigned int);
            case GL_UNSIGNED_BYTE: return sizeof(unsigned char);
        }
        return 0;

    }

};

class BufferLayoutObject
{
    private:
        unsigned int stride = 0;
        unsigned int index  = 0;
        std::vector<LayoutElement> elements;

    public:

        template<typename T>
        void Push(unsigned int count);

        const std::vector<LayoutElement>& GetElements() { return elements; } 
        const unsigned int& GetStride() { return stride; }
        const unsigned int& GetIndex()  { return index;  }

};