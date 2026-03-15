#pragma once
#define GLEW_STATIC
#include "../include/glew.h"
#include "../Scene/Scene.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "../Framebuffer/PickingFramebuffer.h"
#include "../Shader.h"
#include "../Scene/Model.h"
#include "../Window/Window.h"
#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "../include/glm/gtc/type_ptr.hpp"

struct Renderer
{

    PickingFramebuffer fbo;

    void BeginFrame();

    void PickingPass(Shader& shader, Scene &scene);
    void SkyboxPass(Shader& shader, Scene &scene);
    void MainPass(Shader& shader, Scene &scene);
    void LightPass(Shader& shader, Scene &scene);

    void EnableDepthTesting();

    private:

        void DrawMeshes(Shader &shader, Scene &scene);
        void DrawMeshesPicking(Shader &shader, Scene &scene);
        void DrawLightSource(Shader &shader, Scene &scene);
        void DrawLightSourcePicking(Shader &shader, Scene &scene);
    
};