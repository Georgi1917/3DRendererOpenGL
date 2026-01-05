#pragma once
#include <vector>
#include "Model.h"

struct Scene
{

    std::vector<Model *> entities;

    void FreeMem();

};