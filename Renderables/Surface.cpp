#include "Surface.h"

Surface::Surface(glm::vec3 color, Texture *t) 
: Renderable(color, t), surfaceVAO(), surfaceVBO(), surfaceIBO(), layout()
{

    surfaceVAO.Bind();
    surfaceVBO.init(positions, sizeof(positions));
    surfaceIBO.init(indices, 6);
    layout.Push<float>(3);
    layout.Push<float>(3);
    layout.Push<float>(2);
    surfaceVAO.AddBuffer(surfaceVBO, layout);
    surfaceVAO.Unbind();

    translation = glm::vec3(2.0f, -1.5f, 0.0f);
    rotation = glm::vec3(-90.0f, 0.0f, 0.0f);
    scale = glm::vec3(8.0f, 8.0f, 8.0f);

    model = glm::translate(model, translation);
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, scale);

}

Surface::Surface(glm::vec3 color)
: Renderable(color), surfaceVAO(), surfaceVBO(), surfaceIBO(), layout()
{

    surfaceVAO.Bind();
    surfaceVBO.init(positions, sizeof(positions));
    surfaceIBO.init(indices, 6);
    layout.Push<float>(3);
    layout.Push<float>(3);
    layout.Push<float>(2);
    surfaceVAO.AddBuffer(surfaceVBO, layout);
    surfaceVAO.Unbind();

    translation = glm::vec3(2.0f, -1.5f, 0.0f);
    rotation = glm::vec3(-90.0f, 0.0f, 0.0f);
    scale = glm::vec3(8.0f, 8.0f, 8.0f);

    model = glm::translate(model, translation);
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, scale);

}

VertexArray& Surface::GetVAO()
{

    return surfaceVAO;

}

IndexBuffer& Surface::GetIBO()
{

    return surfaceIBO;

}

std::string Surface::GetClassName()
{

    return "Surface";

}

void Surface::Draw()
{

    surfaceVAO.Bind();
    surfaceIBO.Bind();
    glDrawElements(GL_TRIANGLES, surfaceIBO.Count(), GL_UNSIGNED_INT, 0);
    surfaceVAO.Unbind();
    surfaceIBO.Unbind();

}