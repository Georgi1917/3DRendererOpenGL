#include "BufferLayoutObject.h"

template<>
void BufferLayoutObject::Push<float>(unsigned int count)
{

    elements.push_back(LayoutElement{index, count, GL_FLOAT, false});
    index++;
    stride += sizeof(float) * count;

}

template<>
void BufferLayoutObject::Push<unsigned int>(unsigned int count)
{

    elements.push_back(LayoutElement{index, count, GL_UNSIGNED_INT, false});
    index++;
    stride += sizeof(unsigned int) * count;

}

template<>
void BufferLayoutObject::Push<unsigned char>(unsigned int count)
{

    elements.push_back(LayoutElement{index, count, GL_UNSIGNED_BYTE, true});
    index++;
    stride += sizeof(unsigned char) * count;

}

