#include "Renderer.h"
#include <iostream>

void Renderer::Draw(Cube *cube, Shader &shader, unsigned int mode, unsigned int first)
{

    VertexArray& vao = cube->GetVAO();
    shader.SetVec3f("uColor", cube->GetColor());
    vao.Bind();
    glDrawArrays(mode, first, 36);
    vao.Unbind();

}

void Renderer::Draw(Sphere *sphere, Shader &shader, unsigned int mode, unsigned int type)
{

    VertexArray& vao = sphere->GetVAO();
    IndexBuffer& ibo = sphere->GetIBO();
    shader.SetVec3f("uColor", sphere->GetColor());
    vao.Bind();
    ibo.Bind();
    glDrawElements(mode, ibo.Count(), type, 0);
    vao.Unbind();
    ibo.Unbind();

}

void Renderer::DrawPicking(Cube *cube, Shader &shader, unsigned int mode, unsigned int first)
{

    VertexArray& vao = cube->GetVAO();
    shader.SetVec3f("uColor", cube->GetPickingColor());
    vao.Bind();
    glDrawArrays(mode, first, 36);
    vao.Unbind();

}

void Renderer::DrawPicking(Sphere *sphere, Shader &shader, unsigned int mode, unsigned int type)
{

    VertexArray& vao = sphere->GetVAO();
    IndexBuffer& ibo = sphere->GetIBO();
    shader.SetVec3f("uColor", sphere->GetPickingColor());
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