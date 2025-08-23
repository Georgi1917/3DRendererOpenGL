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

class Renderer
{
    public:
        void Draw(Cube *cube, Shader &shader, unsigned int mode, unsigned int first);
        void Draw(Sphere *sphere, Shader &shader, unsigned int mode, unsigned int type);
        void Draw(LightSource *light, Shader &shader, unsigned int mode, unsigned int first);
        void DrawPicking(Cube *cube, Shader &shader, unsigned int mode, unsigned int first);
        void DrawPicking(Sphere *sphere, Shader &shader, unsigned int mode, unsigned int type);
        void DrawPicking(LightSource *light, Shader &shader, unsigned int mode, unsigned int first);
        void Clear();
        void EnableDepthTesting();
        void SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height);
};