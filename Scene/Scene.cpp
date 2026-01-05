#include "Scene.h"

Scene::Scene()
{

    camera = new Camera(glm::vec3(1.0f, 0.0f, 4.0f), glm::vec3(0.0f, 0.0f, -1.0f));
    lightSource = new Light();
    skyBoxModel = ConstructSkyboxM();
    projection = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 1.0f, 100.0f);

}

Scene::~Scene()
{

    for (auto e : entities) delete e;
    entities.clear();

}