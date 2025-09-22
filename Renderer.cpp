#include "Renderer.h"
#include <iostream>

Renderer::Renderer()
{

    source = ConstructCube();
    source->scale = glm::vec3(0.5f, 0.5f, 0.5f);
    source->trans = glm::vec3(2.0f, 2.0f, 0.0f);
    source->color = glm::vec3(1.0f, 1.0f, 1.0f);
    source->SetUpMatrix();

    projection = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 1.0f, 100.0f);

    meshes_c.push_back(ConstructCube());
    meshes_c.push_back(ConstructSphere());
    meshes_c.push_back(LoadObj("obj-files/teapot.obj"));
    meshes_c.push_back(LoadObj("obj-files/teacup.obj"));
    meshes_c.push_back(LoadObj("obj-files/spoon.obj"));

}

Renderer::~Renderer()
{

}


void Renderer::DrawMeshes(Shader &shader)
{

    shader.Bind();
    for (auto &mesh : meshes_c)
    {

        if (mesh->tex != nullptr) 
        {

            mesh->tex->Bind();
            shader.SetBool("hasTex", true);

        }
        else shader.SetBool("hasTex", false);

        shader.SetVec3f("uColor", mesh->color);
        shader.SetVec3f("lColor", source->color);
        shader.SetVec3f("lPos", source->trans);
        shader.SetVec3f("viewPos", cam->GetPosition());
        shader.SetMatrix4fv("model", mesh->model);
        shader.SetMatrix4fv("projection", projection);
        shader.SetMatrix4fv("view", cam->GetViewMatrix());
        mesh->Draw();

        mesh->model = glm::mat4(1.0f);
        mesh->SetUpMatrix();

        if (mesh->tex != nullptr)
            mesh->tex->Unbind();

    }

}

void Renderer::DrawMeshesPicking(Shader &shader)
{

    shader.Bind();

    for (auto& mesh : meshes_c)
    {

        shader.SetVec3f("uColor", mesh->pickingColor);
        shader.SetMatrix4fv("model", mesh->model);
        shader.SetMatrix4fv("projection", projection);
        shader.SetMatrix4fv("view", cam->GetViewMatrix());
        mesh->Draw();

        mesh->model = glm::mat4(1.0f);
        mesh->SetUpMatrix();

    }

}

void Renderer::DrawLightSource(Shader &shader)
{

    shader.Bind();
    shader.SetVec3f("lightColor", source->color);
    shader.SetMatrix4fv("model", source->model);
    shader.SetMatrix4fv("projection", projection);
    shader.SetMatrix4fv("view", cam->GetViewMatrix());
    source->Draw();

    source->model = glm::mat4(1.0f);
    source->SetUpMatrix();

}

void Renderer::DrawLightSourcePicking(Shader& shader)
{

    shader.Bind();
    shader.SetVec3f("lightColor", source->pickingColor);
    shader.SetMatrix4fv("model", source->model);
    shader.SetMatrix4fv("projection", projection);
    shader.SetMatrix4fv("view", cam->GetViewMatrix());
    source->Draw();
    
    source->model = glm::mat4(1.0f);
    source->SetUpMatrix();

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

glm::mat4& Renderer::GetProjection()
{
    return projection;
}
