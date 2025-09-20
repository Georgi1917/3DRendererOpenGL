#include "Renderer.h"
#include <iostream>

std::vector<Vertex> makeCubeVertices() {
    std::vector<Vertex> vertices = {
        
        {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
        {{ 0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
        {{ 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
        {{-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},

        
        {{ 0.5f, -0.5f, -0.5f}, {0.0f, 0.0f,-1.0f}, {0.0f, 0.0f}},
        {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f,-1.0f}, {1.0f, 0.0f}},
        {{-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f,-1.0f}, {1.0f, 1.0f}},
        {{ 0.5f,  0.5f, -0.5f}, {0.0f, 0.0f,-1.0f}, {0.0f, 1.0f}},

        
        {{-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        {{-0.5f, -0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
        {{-0.5f,  0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
        {{-0.5f,  0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},

        
        {{ 0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        {{ 0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
        {{ 0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
        {{ 0.5f,  0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},

        
        {{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
        {{ 0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
        {{ 0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
        {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},

        
        {{-0.5f, -0.5f, -0.5f}, {0.0f,-1.0f, 0.0f}, {0.0f, 0.0f}},
        {{ 0.5f, -0.5f, -0.5f}, {0.0f,-1.0f, 0.0f}, {1.0f, 0.0f}},
        {{ 0.5f, -0.5f,  0.5f}, {0.0f,-1.0f, 0.0f}, {1.0f, 1.0f}},
        {{-0.5f, -0.5f,  0.5f}, {0.0f,-1.0f, 0.0f}, {0.0f, 1.0f}},
    };

    return vertices;
}

std::vector<unsigned int> makeCubeIndices() {
    std::vector<unsigned int> indices = {
        
        0, 1, 2,  2, 3, 0,
        
        4, 5, 6,  6, 7, 4,
        
        8, 9,10, 10,11, 8,
        
       12,13,14, 14,15,12,
        
       16,17,18, 18,19,16,
        
       20,21,22, 22,23,20
    };
    return indices;
}

Mesh* SetUpSphere()
{

    float radius = 1.0f;
    unsigned int stacks = 50;
    unsigned int sectors = 50;

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

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

            glm::vec3 pos = glm::vec3(x, y, z);

            glm::vec3 normal = glm::normalize(glm::vec3(x, y, z));

            float u = (float)j / sectors;
            float v = (float)i / stacks;

            vertices.push_back(
                {{pos}, {normal}, {u, v}}
            );

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

    Mesh* mesh = new Mesh();
    mesh->Init(vertices, indices);

    return mesh;

}

Renderer::Renderer()
{

    source = new Mesh();
    source->Init(makeCubeVertices(), makeCubeIndices());
    source->scale = glm::vec3(0.5f, 0.5f, 0.5f);
    source->trans = glm::vec3(2.0f, 2.0f, 0.0f);
    source->color = glm::vec3(1.0f, 1.0f, 1.0f);
    source->SetUpMatrix();

    projection = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 1.0f, 100.0f);

    Mesh *mesh = new Mesh();
    mesh->Init(makeCubeVertices(), makeCubeIndices());
    meshes_c.push_back(mesh);
    meshes_c.push_back(SetUpSphere());

}

Renderer::~Renderer()
{

}


void Renderer::DrawMeshes(Shader &shader)
{

    shader.Bind();
    for (auto &mesh : meshes_c)
    {

        shader.SetVec3f("uColor", mesh->color);
        shader.SetVec3f("lColor", source->color);
        shader.SetVec3f("lPos", source->trans);
        shader.SetVec3f("viewPos", cam->GetPosition());
        shader.SetMatrix4fv("model", mesh->model);
        shader.SetMatrix4fv("projection", projection);
        shader.SetMatrix4fv("view", cam->GetViewMatrix());
        mesh->Draw();
        mesh->model = glm::mat4(1.0f);
        mesh->SetUpMatrix();

    }

}

void Renderer::DrawMeshesPicking(Shader &shader)
{

    shader.Bind();

    for (auto& mesh : meshes_c)
    {

        shader.SetVec3f("uColor", mesh->pickingColor);
        shader.SetMatrix4fv("model", mesh->model);
        shader.SetMatrix4fv("projection", projection);
        shader.SetMatrix4fv("view", cam->GetViewMatrix());
        mesh->Draw();
        mesh->model = glm::mat4(1.0f);
        mesh->SetUpMatrix();

    }

}

void Renderer::DrawLightSource(Shader &shader)
{

    shader.Bind();
    shader.SetVec3f("lightColor", source->color);
    shader.SetMatrix4fv("model", source->model);
    shader.SetMatrix4fv("projection", projection);
    shader.SetMatrix4fv("view", cam->GetViewMatrix());
    source->Draw();
    source->model = glm::mat4(1.0f);
    source->SetUpMatrix();

}

void Renderer::DrawLightSourcePicking(Shader& shader)
{

    shader.Bind();
    shader.SetVec3f("lightColor", source->pickingColor);
    shader.SetMatrix4fv("model", source->model);
    shader.SetMatrix4fv("projection", projection);
    shader.SetMatrix4fv("view", cam->GetViewMatrix());
    source->Draw();
    source->model = glm::mat4(1.0f);
    source->SetUpMatrix();

}

void Renderer::SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
{

    glViewport(x, y, width, height);

}

void Renderer::Clear()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void Renderer::EnableDepthTesting()
{

    glEnable(GL_DEPTH_TEST);

}

glm::mat4& Renderer::GetProjection()
{
    return projection;
}

void Renderer::SetCamera(Camera *camera)
{

    cam = camera;

}

void Renderer::AddMesh(Renderable *mesh)
{

    meshes.push_back(mesh);

}

std::vector<Mesh *>& Renderer::GetMeshes()
{

    return meshes_c;

}

void Renderer::DeleteObject(Renderable *obj)
{

    for (auto it = meshes.begin(); it != meshes.end();)
    {

        if (*it == obj) it = meshes.erase(it);
        else ++it;

    }

}

Mesh*& Renderer::GetLightSource()
{

    return source;

}