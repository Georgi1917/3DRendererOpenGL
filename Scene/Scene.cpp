#include "Scene.h"

Scene::Scene()
{

    camera = new Camera(glm::vec3(1.0f, 0.0f, 4.0f), glm::vec3(0.0f, 0.0f, -1.0f));
    lightSource = new Light();
    skyBoxTexture = new Cubemap({

        "cubemap-faces/right.jpg",
        "cubemap-faces/left.jpg",
        "cubemap-faces/top.jpg",
        "cubemap-faces/bottom.jpg",
        "cubemap-faces/front.jpg",
        "cubemap-faces/back.jpg",

    });
    skyBoxModel = ConstructSkyboxM();
    projection = glm::perspective(glm::radians(75.0f), 1280.0f / 720.0f, 1.0f, 300.0f);

    entities.push_back(new Model("obj-files/wizard.blend"));

}

Scene::~Scene()
{

    for (auto e : entities) delete e;
    entities.clear();

}

void Scene::ResetProjection(int width, int height)
{

    projection = glm::perspective(glm::radians(75.0f), (float)width / (float)height, 1.0f, 300.0f);

}