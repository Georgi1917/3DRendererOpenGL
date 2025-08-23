#include "LightSource.h"

LightSource::LightSource() : lightVAO(), lightVBO(), layout()
{

    color = glm::vec3(1.0f, 1.0f, 1.0f);
    translation = glm::vec3(5.0f, 5.0f, 0.0f);
    scale = glm::vec3(0.5f, 0.5f, 0.5f);

    lightVAO.Bind();
    lightVBO.init(positions, sizeof(positions));
    layout.Push<float>(3);
    lightVAO.AddBuffer(lightVBO, layout);
    lightVAO.Unbind();

}

LightSource::~LightSource()
{



}

unsigned int LightSource::GetNumberOfVertices()
{

    return numOfVertices;

}

VertexArray& LightSource::GetVAO()
{

    return lightVAO;

}

std::string LightSource::GetClassName()
{

    return "Light Source";

}