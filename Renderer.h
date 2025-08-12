#pragma once
#define GLEW_STATIC
#include "include/glew.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Renderables/Renderable.h"
#include "Renderables/Cube.h"
#include "Renderables/Sphere.h"

class Renderer
{
    public:
        void Draw(Cube *cube, Shader &shader, unsigned int mode, unsigned int first);
        void Draw(Sphere *sphere, Shader &shader, unsigned int mode, unsigned int type);
        void DrawPicking(Cube *cube, Shader &shader, unsigned int mode, unsigned int first);
        void DrawPicking(Sphere *sphere, Shader &shader, unsigned int mode, unsigned int type);
        void Clear();
        void EnableDepthTesting();
};