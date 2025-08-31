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

            glm::vec3 normal = glm::normalize(glm::vec3(x, y, z));
            vertices.push_back(normal.x);
            vertices.push_back(normal.y);
            vertices.push_back(normal.z);

            float u = (float)j / sectors;
            float v = (float)i / stacks;
            vertices.push_back(u);
            vertices.push_back(v);

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
    layout.Push<float>(2);
    sphereVAO.AddBuffer(sphereVBO, layout);
    sphereVAO.Unbind();

}

Sphere::Sphere(glm::vec3 _color, Texture *t, float _radius, unsigned int _stacks, unsigned int _sectors) : 
    Renderable(_color, t), 
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
    layout.Push<float>(2);
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

void Sphere::Draw()
{

    tex->Bind();
    sphereVAO.Bind();
    sphereIBO.Bind();
    glDrawElements(GL_TRIANGLES, sphereIBO.Count(), GL_UNSIGNED_INT, 0);
    sphereVAO.Unbind();
    sphereIBO.Unbind();
    tex->Unbind();

}