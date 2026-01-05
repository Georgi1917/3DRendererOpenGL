#include "Scene.h"

void Scene::FreeMem()
{

    for (auto e : entities) delete e;
    entities.clear();

}