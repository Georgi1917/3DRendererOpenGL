#include "Renderer.h"
#include <iostream>

Renderer::Renderer()
{

    source = new LightSource();
    projection = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 1.0f, 100.0f);
    meshes.push_back(new Cube(glm::vec3(1.0f, 1.0f, 0.0f)));
    meshes.push_back(new Sphere(glm::vec3(1.0f, 0.0f, 0.0f), 1.0f, 50, 50));
    meshes.push_back(new Cube(glm::vec3(0.8f, 1.0f, 0.2f)));

}

Renderer::~Renderer()
{

}

void Renderer::DrawMeshes(Shader &shader)
{

    shader.Bind();

    for (auto& mesh : meshes)
    {

        shader.SetVec3f("uColor", mesh->GetColor());
        shader.SetVec3f("lColor", mesh->GetLightColor());
        shader.SetVec3f("lPos", source->GetTranslation());
        shader.SetVec3f("viewPos", cam->GetPosition());
        shader.SetMatrix4fv("model", mesh->GetModelMatrix());
        shader.SetMatrix4fv("projection", projection);
        shader.SetMatrix4fv("view", cam->GetViewMatrix());
        mesh->Draw();
        mesh->ResetModelMatrix();

    }

}

void Renderer::DrawMeshesPicking(Shader &shader)
{

    shader.Bind();

    for (auto& mesh : meshes)
    {

        shader.SetVec3f("uColor", mesh->GetPickingColor());
        shader.SetMatrix4fv("model", mesh->GetModelMatrix());
        shader.SetMatrix4fv("projection", projection);
        shader.SetMatrix4fv("view", cam->GetViewMatrix());
        mesh->Draw();
        mesh->ResetModelMatrix();

    }

}

void Renderer::DrawLightSource(Shader &shader)
{

    shader.Bind();
    shader.SetVec3f("lightColor", source->GetColor());
    shader.SetMatrix4fv("model", source->GetModelMatrix());
    shader.SetMatrix4fv("projection", projection);
    shader.SetMatrix4fv("view", cam->GetViewMatrix());
    source->Draw();
    source->ResetModelMatrix();

}

void Renderer::DrawLightSourcePicking(Shader& shader)
{

    shader.Bind();
    shader.SetVec3f("lightColor", source->GetPickingColor());
    shader.SetMatrix4fv("model", source->GetModelMatrix());
    shader.SetMatrix4fv("projection", projection);
    shader.SetMatrix4fv("view", cam->GetViewMatrix());
    source->Draw();
    source->ResetModelMatrix();

}

// void Renderer::Draw(Cube *cube, Shader &shader, unsigned int mode, unsigned int first)
// {

//     shader.Bind();
//     VertexArray& vao = cube->GetVAO();
//     shader.SetVec3f("uColor", cube->GetColor());
//     shader.SetVec3f("lColor", cube->GetLightColor());
//     shader.SetVec3f("lPos", source->GetTranslation());
//     shader.SetVec3f("viewPos", cam->GetPosition());
//     shader.SetMatrix4fv("model", cube->GetModelMatrix());
//     shader.SetMatrix4fv("projection", projection);
//     shader.SetMatrix4fv("view", cam->GetViewMatrix());
//     vao.Bind();
//     glDrawArrays(mode, first, 36);
//     vao.Unbind();

// }

// void Renderer::Draw(Sphere *sphere, Shader &shader, unsigned int mode, unsigned int type)
// {

//     shader.Bind();
//     VertexArray& vao = sphere->GetVAO();
//     IndexBuffer& ibo = sphere->GetIBO();
//     shader.SetVec3f("uColor", sphere->GetColor());
//     shader.SetVec3f("lColor", sphere->GetLightColor());
//     shader.SetVec3f("lPos", source->GetTranslation());
//     shader.SetVec3f("viewPos", cam->GetPosition());
//     shader.SetMatrix4fv("model", sphere->GetModelMatrix());
//     shader.SetMatrix4fv("projection", projection);
//     shader.SetMatrix4fv("view", cam->GetViewMatrix());
//     vao.Bind();
//     ibo.Bind();
//     glDrawElements(mode, ibo.Count(), type, 0);
//     vao.Unbind();
//     ibo.Unbind();

// }

// void Renderer::Draw(LightSource *light, Shader &shader, unsigned int mode, unsigned int first)
// {

//     shader.Bind();
//     VertexArray& vao = light->GetVAO();
//     shader.SetVec3f("lightColor", light->GetColor());
//     shader.SetMatrix4fv("model", light->GetModelMatrix());
//     shader.SetMatrix4fv("projection", projection);
//     shader.SetMatrix4fv("view", cam->GetViewMatrix());
//     vao.Bind();
//     glDrawArrays(mode, first, 36);
//     vao.Unbind();

// }

// void Renderer::DrawPicking(Cube *cube, Shader &shader, unsigned int mode, unsigned int first)
// {

//     shader.Bind();
//     VertexArray& vao = cube->GetVAO();
//     shader.SetVec3f("uColor", cube->GetPickingColor());
//     shader.SetMatrix4fv("model", cube->GetModelMatrix());
//     shader.SetMatrix4fv("projection", projection);
//     shader.SetMatrix4fv("view", cam->GetViewMatrix());
//     vao.Bind();
//     glDrawArrays(mode, first, 36);
//     vao.Unbind();

// }

// void Renderer::DrawPicking(Sphere *sphere, Shader &shader, unsigned int mode, unsigned int type)
// {

//     shader.Bind();
//     VertexArray& vao = sphere->GetVAO();
//     IndexBuffer& ibo = sphere->GetIBO();
//     shader.SetVec3f("uColor", sphere->GetPickingColor());
//     shader.SetMatrix4fv("model", sphere->GetModelMatrix());
//     shader.SetMatrix4fv("projection", projection);
//     shader.SetMatrix4fv("view", cam->GetViewMatrix());
//     vao.Bind();
//     ibo.Bind();
//     glDrawElements(mode, ibo.Count(), type, 0);
//     vao.Unbind();
//     ibo.Unbind();

// }

// void Renderer::DrawPicking(LightSource *light, Shader &shader, unsigned int mode, unsigned int first)
// {

//     shader.Bind();
//     VertexArray& vao = light->GetVAO();
//     shader.SetVec3f("lightColor", light->GetPickingColor());
//     shader.SetMatrix4fv("model", light->GetModelMatrix());
//     shader.SetMatrix4fv("projection", projection);
//     shader.SetMatrix4fv("view", cam->GetViewMatrix());
//     vao.Bind();
//     glDrawArrays(mode, first, 36);
//     vao.Unbind();

// }

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

glm::mat4& Renderer::GetProjection()
{
    return projection;
}

void Renderer::SetCamera(Camera *camera)
{

    cam = camera;

}

void Renderer::SetLightSource(LightSource *lSource)
{

    source = lSource;

}

LightSource*& Renderer::GetLightSource()
{

    return source;

}

void Renderer::AddMesh(Renderable *mesh)
{

    meshes.push_back(mesh);

}

std::vector<Renderable *>& Renderer::GetMeshes()
{

    return meshes;

}