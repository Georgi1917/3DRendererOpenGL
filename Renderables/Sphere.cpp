#include "Sphere.h"

void Sphere::SetUpSphere()
{

    for (unsigned int i = 0; i <= stacks; ++i)
    {

        float stackAngle = glm::pi<float>() / 2 - i * glm::pi<float>() / stacks;
        float xy = radius * cosf(stackAngle);
        float z = radius * sinf(stackAngle);

        for (unsigned int j = 0; j <= sectors; ++j)
        {

            float sectorAngle = j * 2 * glm::pi<float>() / sectors;

            float x = xy * cosf(sectorAngle);
            float y = xy * sinf(sectorAngle);

            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);

            vertices.push_back(1.0f);
            vertices.push_back(0.0f);
            vertices.push_back(0.0f);

        }

    }

    for (unsigned int i = 0; i < stacks; ++i)
    {

        unsigned int k1 = i * (sectors + 1);
        unsigned int k2 = k1 + sectors + 1;

        for (unsigned int j = 0; j < sectors; ++j, ++k1, ++k2)
        {

            if (i != 0)
            {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }

            if (i != (stacks - 1))
            {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }

        }

    }

}

Sphere::Sphere(glm::vec3 _color, float _radius, unsigned int _stacks, unsigned int _sectors) : 
    Renderable(_color), 
    sphereVAO(), 
    sphereVBO(),
    sphereIBO(),
    layout(),
    radius(_radius), stacks(_stacks), sectors(_sectors)
{

    SetUpSphere();
    sphereVAO.Bind();
    sphereVBO.init(vertices.data(), vertices.size() * sizeof(float));
    sphereIBO.init(indices.data(), indices.size());
    layout.Push<float>(3);
    layout.Push<float>(3);

    sphereVAO.AddBuffer(sphereVBO, layout);
    sphereVAO.Unbind();

}

Sphere::~Sphere()
{
    
}

VertexArray& Sphere::GetVAO()
{
    return sphereVAO;
}

IndexBuffer& Sphere::GetIBO()
{
    return sphereIBO;
}

std::string Sphere::GetClassName()
{

    return "Sphere";

}