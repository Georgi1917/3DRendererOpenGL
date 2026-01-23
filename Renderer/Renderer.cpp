#include "Renderer.h"
#include <iostream>

void Renderer::BeginFrame()
{

    glViewport(0, 0, 1280, 720);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void Renderer::PickingPass(Shader& shader)
{

    fbo.Bind();
    glViewport(0, 0, 1280, 720);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    DrawMeshesPicking(shader);
    DrawLightSourcePicking(shader);
    fbo.Unbind();

}

void Renderer::MainPass(Shader& shader)
{

    DrawMeshes(shader);

}

void Renderer::SkyboxPass(Shader& shader)
{

    glViewport(0, 0, 1280, 720);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (!scene.hasSkybox) return;

    glm::mat4 view = glm::mat4(glm::mat3(scene.camera->GetViewMatrix()));

    glDepthMask(GL_FALSE);
    glDepthFunc(GL_LEQUAL);
    shader.Bind();
    scene.skyBoxTexture->Bind();
    shader.SetMatrix4fv("projection", scene.projection);
    shader.SetMatrix4fv("view", view);
    shader.SetMatrix4fv("model", scene.skyBoxModel->model);
    scene.skyBoxModel->Draw(shader);
    scene.skyBoxModel->model = glm::mat4(1.0f);
    scene.skyBoxModel->SetUpMatrix();
    scene.skyBoxTexture->Unbind();
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);

}

void Renderer::LightPass(Shader &shader)
{

    DrawLightSource(shader);

}

void Renderer::DrawMeshes(Shader &shader)
{

    shader.Bind();

    shader.SetMatrix4fv("projection", scene.projection);
    shader.SetMatrix4fv("view", scene.camera->GetViewMatrix());

    if (scene.entities.empty())
    {

        std::cout << "YESS" << "\n";

    }

    for (auto& entity : scene.entities)
    {

        shader.SetVec3f("light.pos", scene.lightSource->mesh->trans);
        shader.SetVec3f("light.ambient", scene.lightSource->ambient);
        shader.SetVec3f("light.diffuse", scene.lightSource->diffuse);
        shader.SetVec3f("light.specular", scene.lightSource->specular);
        scene.lightSource->hasAttenuation ? shader.SetBool("light.hasAttenuation", true) 
                                          : shader.SetBool("light.hasAttenuation", false);
        shader.SetVec3f("viewPos", scene.camera->GetPosition());
        shader.SetMatrix4fv("model", entity->model);
        entity->Draw(shader);

        entity->model = glm::mat4(1.0f);
        entity->SetUpMatrix();

    }

}

void Renderer::DrawMeshesPicking(Shader &shader)
{

    shader.Bind();
    shader.SetMatrix4fv("projection", scene.projection);
    shader.SetMatrix4fv("view", scene.camera->GetViewMatrix());

    for (auto& model : scene.entities)
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
    shader.SetVec3f("uColor", scene.lightSource->lightColor);
    shader.SetMatrix4fv("model", scene.lightSource->mesh->model);
    shader.SetMatrix4fv("projection", scene.projection);
    shader.SetMatrix4fv("view", scene.camera->GetViewMatrix());
    scene.lightSource->mesh->Draw(shader);

    scene.lightSource->mesh->model = glm::mat4(1.0f);
    scene.lightSource->mesh->SetUpMatrix();

}

void Renderer::DrawLightSourcePicking(Shader& shader)
{

    shader.Bind();
    shader.SetVec3f("uColor", scene.lightSource->mesh->pickingColor);
    shader.SetMatrix4fv("model", scene.lightSource->mesh->model);
    shader.SetMatrix4fv("projection", scene.projection);
    shader.SetMatrix4fv("view", scene.camera->GetViewMatrix());
    scene.lightSource->mesh->Draw(shader);
    
    scene.lightSource->mesh->model = glm::mat4(1.0f);
    scene.lightSource->mesh->SetUpMatrix();

}

void Renderer::EnableDepthTesting()
{

    glEnable(GL_DEPTH_TEST);

}

