#pragma once
#define GLEW_STATIC
#include "include/glew.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Renderables/Mesh.h"
#include "Camera.h"
#include "include/glm/glm.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include "include/glm/gtc/type_ptr.hpp"

struct Renderer
{

    glm::mat4 projection;
    Camera *cam;
    Mesh *source;
    std::vector<Mesh *> meshes_c;

    Renderer();
    ~Renderer();

    void DrawMeshes(Shader &shader);
    void DrawMeshesPicking(Shader &shader);
    void DrawLightSource(Shader &shader);
    void DrawLightSourcePicking(Shader &shader);
    void Clear();
    void EnableDepthTesting();
    void SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height);
    glm::mat4& GetProjection();
    
};