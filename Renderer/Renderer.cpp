#include "Renderer.h"
#include <iostream>

void Renderer::BeginFrame()
{

    glViewport(0, 0, GetCurrentContext()->width, GetCurrentContext()->height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void Renderer::PickingPass(Shader& shader, Scene &scene)
{

    fbo.Bind();
    glViewport(0, 0, GetCurrentContext()->width, GetCurrentContext()->height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    DrawMeshesPicking(shader, scene);
    DrawLightSourcePicking(shader, scene);
    fbo.Unbind();

}

void Renderer::MainPass(Shader& shader, Scene &scene)
{

    DrawMeshes(shader, scene);

}

void Renderer::SkyboxPass(Shader& shader, Scene &scene)
{

    glViewport(0, 0, GetCurrentContext()->width, GetCurrentContext()->height);
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
    
    scene.skyBoxTexture->Unbind();
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);

}

void Renderer::LightPass(Shader &shader, Scene &scene)
{

    DrawLightSource(shader, scene);

}

void Renderer::DrawMeshes(Shader &shader, Scene &scene)
{

    shader.Bind();

    shader.SetMatrix4fv("projection", scene.projection);
    shader.SetMatrix4fv("view", scene.camera->GetViewMatrix());
    shader.SetVec3f("light.pos", scene.lightSource->mesh->trans);
    shader.SetVec3f("light.ambient", scene.lightSource->ambient);
    shader.SetVec3f("light.diffuse", scene.lightSource->diffuse);
    shader.SetVec3f("light.specular", scene.lightSource->specular);
    scene.lightSource->hasAttenuation ? shader.SetBool("light.hasAttenuation", true) 
                                        : shader.SetBool("light.hasAttenuation", false);
    shader.SetVec3f("viewPos", scene.camera->GetPosition());

    for (auto& entity : scene.entities)
    {

        shader.SetMatrix4fv("model", entity->model);
        entity->Draw(shader);

    }

}

void Renderer::DrawMeshesPicking(Shader &shader, Scene &scene)
{

    shader.Bind();
    shader.SetMatrix4fv("projection", scene.projection);
    shader.SetMatrix4fv("view", scene.camera->GetViewMatrix());

    for (auto& model : scene.entities)
    {

        shader.SetVec3f("uColor", model->pickingColor);
        shader.SetMatrix4fv("model", model->model);
        model->Draw(shader);

    }

}

void Renderer::DrawLightSource(Shader &shader, Scene &scene)
{

    shader.Bind();
    shader.SetVec3f("uColor", scene.lightSource->lightColor);
    shader.SetMatrix4fv("model", scene.lightSource->mesh->model);
    shader.SetMatrix4fv("projection", scene.projection);
    shader.SetMatrix4fv("view", scene.camera->GetViewMatrix());
    scene.lightSource->mesh->Draw(shader);

}

void Renderer::DrawLightSourcePicking(Shader& shader, Scene &scene)
{

    shader.Bind();
    shader.SetVec3f("uColor", scene.lightSource->mesh->pickingColor);
    shader.SetMatrix4fv("model", scene.lightSource->mesh->model);
    shader.SetMatrix4fv("projection", scene.projection);
    shader.SetMatrix4fv("view", scene.camera->GetViewMatrix());
    scene.lightSource->mesh->Draw(shader);

}

void Renderer::EnableDepthTesting()
{

    glEnable(GL_DEPTH_TEST);

}

