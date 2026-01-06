#pragma once
#include <vector>
#include "Model.h"
#include "Light.h"
#include "../Camera.h"
#include "../Textures/Cubemap.h"

struct Scene
{

    Camera    *camera;
    Light     *lightSource;
    Model     *skyBoxModel;
    Cubemap   *skyBoxTexture;
    glm::mat4  projection;

    bool hasSkybox = true;

    std::vector<Model *> entities;

    Scene();
    ~Scene();

};