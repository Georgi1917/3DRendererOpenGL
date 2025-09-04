#pragma once
#define GLEW_STATIC
#include "include/glew.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Renderables/Renderable.h"
#include "Renderables/Cube.h"
#include "Renderables/Sphere.h"
#include "Renderables/LightSource.h"
#include "Camera.h"
#include "include/glm/glm.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include "include/glm/gtc/type_ptr.hpp"

class Renderer
{

    private:
    
        glm::mat4 projection;
        Camera *cam;
        LightSource *source;
        std::vector<Renderable *> meshes;

    public:

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
        void SetCamera(Camera* camera);
        void SetLightSource(LightSource *lSource);
        LightSource*& GetLightSource();
        void AddMesh(Renderable *mesh);
        std::vector<Renderable *>& GetMeshes();
        void DeleteObject(Renderable * obj);
};