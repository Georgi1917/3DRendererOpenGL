#include "Model.h"

void Model::Draw(Shader& shader)
{

    shader.SetMatrix4fv("model", model);

    for (auto& mesh : modelMeshes)
    {

        mesh.Draw(shader);

    }

}