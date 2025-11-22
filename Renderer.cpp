#include "Renderer.h"
#include <iostream>

Renderer::Renderer()
{

    Light *l = new Light();
    l->Init();
    source = l;

    projection = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 1.0f, 100.0f);

    skyBoxM = ConstructSkyboxM();

    models_c.push_back(ConstructCubeM());
    models_c.push_back(ConstructSphereM());
    models_c.push_back(ConstructPyramidM());

}

Renderer::~Renderer()
{

}

void Renderer::DrawSkybox(Shader &shader)
{

    if (!hasSkybox) return;

    stbi_set_flip_vertically_on_load(false);

    glm::mat4 view = glm::mat4(glm::mat3(cam->GetViewMatrix()));

    glDepthMask(GL_FALSE);
    glDepthFunc(GL_LEQUAL);
    shader.Bind();
    skyBoxTexture->Bind();
    shader.SetMatrix4fv("projection", projection);
    shader.SetMatrix4fv("view", view);
    shader.SetMatrix4fv("model", skyBoxM->model);
    skyBoxM->Draw(shader);
    skyBoxM->model = glm::mat4(1.0f);
    skyBoxM->SetUpMatrix();
    skyBoxTexture->Unbind();
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);

    stbi_set_flip_vertically_on_load(true);

}

void Renderer::DrawMeshes(Shader &shader)
{

    shader.Bind();

    shader.SetMatrix4fv("projection", projection);
    shader.SetMatrix4fv("view", cam->GetViewMatrix());

    for (auto& model : models_c)
    {

        if (hasAttenuation) shader.SetBool("hasAttenuation", true);
        else shader.SetBool("hasAttenuation", false);

        shader.SetVec3f("light.pos", source->mesh->trans);
        shader.SetVec3f("light.ambient", source->ambient);
        shader.SetVec3f("light.diffuse", source->diffuse);
        shader.SetVec3f("light.specular", source->specular);
        shader.SetVec3f("viewPos", cam->GetPosition());
        shader.SetMatrix4fv("model", model->model);
        model->Draw(shader);

        model->model = glm::mat4(1.0f);
        model->SetUpMatrix();

    }

}

void Renderer::DrawMeshesPicking(Shader &shader)
{

    shader.Bind();
    shader.SetMatrix4fv("projection", projection);
    shader.SetMatrix4fv("view", cam->GetViewMatrix());

    for (auto& model : models_c)
    {

        shader.SetVec3f("uColor", model->pickingColor);
        shader.SetMatrix4fv("model", model->model);
        model->Draw(shader);

        model->model = glm::mat4(1.0f);
        model->SetUpMatrix();

    }

}

void Renderer::DrawLightSource(Shader &shader)
{

    shader.Bind();
    shader.SetVec3f("lightColor", source->lightColor);
    shader.SetMatrix4fv("model", source->mesh->model);
    shader.SetMatrix4fv("projection", projection);
    shader.SetMatrix4fv("view", cam->GetViewMatrix());
    source->mesh->Draw(shader);

    source->mesh->model = glm::mat4(1.0f);
    source->mesh->SetUpMatrix();

}

void Renderer::DrawLightSourcePicking(Shader& shader)
{

    shader.Bind();
    shader.SetVec3f("lightColor", source->mesh->pickingColor);
    shader.SetMatrix4fv("model", source->mesh->model);
    shader.SetMatrix4fv("projection", projection);
    shader.SetMatrix4fv("view", cam->GetViewMatrix());
    source->mesh->Draw(shader);
    
    source->mesh->model = glm::mat4(1.0f);
    source->mesh->SetUpMatrix();

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
