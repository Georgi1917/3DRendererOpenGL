#include "Renderer.h"
#include <iostream>

void Renderer::Draw(Cube *cube, Shader &shader, unsigned int mode, unsigned int first)
{

    VertexArray& vao = cube->GetVAO();
    shader.SetVec3f("uColor", cube->GetColor());
    shader.SetVec3f("lColor", cube->GetLightColor());
    shader.SetMatrix4fv("model", cube->GetModelMatrix());
    vao.Bind();
    glDrawArrays(mode, first, 36);
    vao.Unbind();

}

void Renderer::Draw(Sphere *sphere, Shader &shader, unsigned int mode, unsigned int type)
{

    VertexArray& vao = sphere->GetVAO();
    IndexBuffer& ibo = sphere->GetIBO();
    shader.SetVec3f("uColor", sphere->GetColor());
    shader.SetVec3f("lColor", sphere->GetLightColor());
    //std::cout << sphere->GetLightColor().r << sphere->GetLightColor().g << sphere->GetLightColor().b << "\n";
    shader.SetMatrix4fv("model", sphere->GetModelMatrix());
    vao.Bind();
    ibo.Bind();
    glDrawElements(mode, ibo.Count(), type, 0);
    vao.Unbind();
    ibo.Unbind();

}

void Renderer::Draw(LightSource *light, Shader &shader, unsigned int mode, unsigned int first)
{

    VertexArray& vao = light->GetVAO();
    shader.SetVec3f("lightColor", light->GetColor());
    shader.SetMatrix4fv("model", light->GetModelMatrix());
    vao.Bind();
    glDrawArrays(mode, first, 36);
    vao.Unbind();

}

void Renderer::DrawPicking(Cube *cube, Shader &shader, unsigned int mode, unsigned int first)
{

    VertexArray& vao = cube->GetVAO();
    shader.SetVec3f("uColor", cube->GetPickingColor());
    shader.SetVec3f("lColor", cube->GetLightColor());
    shader.SetMatrix4fv("model", cube->GetModelMatrix());
    vao.Bind();
    glDrawArrays(mode, first, 36);
    vao.Unbind();

}

void Renderer::DrawPicking(Sphere *sphere, Shader &shader, unsigned int mode, unsigned int type)
{

    VertexArray& vao = sphere->GetVAO();
    IndexBuffer& ibo = sphere->GetIBO();
    shader.SetVec3f("uColor", sphere->GetPickingColor());
    shader.SetVec3f("lColor", sphere->GetLightColor());
    shader.SetMatrix4fv("model", sphere->GetModelMatrix());
    vao.Bind();
    ibo.Bind();
    glDrawElements(mode, ibo.Count(), type, 0);
    vao.Unbind();
    ibo.Unbind();

}

void Renderer::DrawPicking(LightSource *light, Shader &shader, unsigned int mode, unsigned int first)
{

    VertexArray& vao = light->GetVAO();
    shader.SetVec3f("lightColor", light->GetPickingColor());
    shader.SetMatrix4fv("model", light->GetModelMatrix());
    vao.Bind();
    glDrawArrays(mode, first, 36);
    vao.Unbind();

}

void Renderer::SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
{

    glViewport(x, y, width, height);

}

void Renderer::Clear()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void Renderer::EnableDepthTesting()
{

    glEnable(GL_DEPTH_TEST);

}