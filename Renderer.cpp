#include "Renderer.h"
#include <iostream>

void Renderer::DrawArrays(VertexArray& vao, unsigned int mode, unsigned int first, unsigned int indicesCount)
{

    vao.Bind();
    glDrawArrays(mode, first, indicesCount);
    vao.Unbind();

}

void Renderer::DrawElements(VertexArray& vao, IndexBuffer& ibo, unsigned int mode, unsigned int type)
{

    vao.Bind();
    ibo.Bind();
    glDrawElements(mode, ibo.Count(), type, 0);
    vao.Unbind();
    ibo.Unbind();

}

void Renderer::Draw(Cube *cube, unsigned int mode, unsigned int first)
{

    VertexArray& vao = cube->GetVAO();
    vao.Bind();
    glDrawArrays(mode, first, 36);
    vao.Unbind();

}

void Renderer::Draw(Sphere *sphere, unsigned int mode, unsigned int type)
{

    VertexArray& vao = sphere->GetVAO();
    IndexBuffer& ibo = sphere->GetIBO();
    vao.Bind();
    ibo.Bind();
    glDrawElements(mode, ibo.Count(), type, 0);
    vao.Unbind();
    ibo.Unbind();

}

void Renderer::Clear()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void Renderer::EnableDepthTesting()
{

    glEnable(GL_DEPTH_TEST);

}