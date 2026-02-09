#pragma once
#define GLEW_STATIC
#include "../include/glew.h"
#include "../Scene/Scene.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "../Framebuffer/PickingFramebuffer.h"
#include "../Shader.h"
#include "../Scene/Mesh.h"
#include "../Scene/Light.h"
#include "../Scene/Model.h"
#include "../Camera.h"
#include "../Textures/Cubemap.h"
#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "../include/glm/gtc/type_ptr.hpp"

struct Renderer
{

    Scene scene;
    
    PickingFramebuffer fbo;

    void BeginFrame();

    void PickingPass(Shader& shader);
    void SkyboxPass(Shader& shader);
    void MainPass(Shader& shader);
    void LightPass(Shader& shader);

    void EnableDepthTesting();

    private:

        void DrawMeshes(Shader &shader);
        void DrawMeshesPicking(Shader &shader);
        void DrawLightSource(Shader &shader);
        void DrawLightSourcePicking(Shader &shader);
    
};