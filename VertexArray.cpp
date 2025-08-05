#define GLEW_STATIC
#include "include/glew.h"
#include "VertexArray.h"
#include <cstddef>

VertexArray::VertexArray()
{

    glGenVertexArrays(1, &rendererID);
    glBindVertexArray(rendererID);

}

VertexArray::~VertexArray()
{

    glDeleteVertexArrays(1, &rendererID);

}

void VertexArray::AddBuffer(VertexBuffer& vbo, BufferLayoutObject& layout)
{

    vbo.Bind();

    std::vector<LayoutElement> elements = layout.GetElements();
    size_t offset = 0;

    for (unsigned int i = 0; i < elements.size(); i++)
    {

        LayoutElement currEl = elements[i];
        glVertexAttribPointer(currEl.index, currEl.count, currEl.type, currEl.normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (void*)offset);
        glEnableVertexAttribArray(currEl.index);
        offset += currEl.count * currEl.GetType();

    }

    vbo.Unbind();

}

void VertexArray::Bind()
{

    glBindVertexArray(rendererID);

}

void VertexArray::Unbind()
{

    glBindVertexArray(0);

}