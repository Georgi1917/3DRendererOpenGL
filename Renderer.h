#pragma once
#define GLEW_STATIC
#include "include/glew.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Renderables/Mesh.h"
#include "Renderables/Light.h"
#include "Camera.h"
#include "Textures/Cubemap.h"
#include "include/glm/glm.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include "include/glm/gtc/type_ptr.hpp"

struct Renderer
{

    glm::mat4 projection;
    Camera *cam;
    Light *source;
    Mesh *skyBox;
    Cubemap *skyBoxTexture;

    std::vector<Mesh *> meshes_c;
    bool hasAttenuation = true;
    bool hasSkybox      = true;

    Renderer();
    ~Renderer();

    void DrawSkybox(Shader &shader);
    void DrawMeshes(Shader &shader);
    void DrawMeshesPicking(Shader &shader);
    void DrawLightSource(Shader &shader);
    void DrawLightSourcePicking(Shader &shader);
    void Clear();
    void EnableDepthTesting();
    void SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height);
    glm::mat4& GetProjection();
    
};