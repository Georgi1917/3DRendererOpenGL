#pragma once

#include "Renderable.h"

class Surface : public Renderable
{

    private:
        float positions[24] = {
             -0.5f,   0.5f,   0.0f,   0.0f, 0.0f, 1.0f, 
              0.5f,   0.5f,   0.0f,   0.0f, 0.0f, 1.0f,
              0.5f,  -0.5f,   0.0f,   0.0f, 0.0f, 1.0f,
             -0.5f,  -0.5f,   0.0f,   0.0f, 0.0f, 1.0f
        };
        unsigned int indices[6] = {
            0, 1, 2,
            2, 3, 0
        };

        VertexArray surfaceVAO;
        VertexBuffer surfaceVBO;
        IndexBuffer surfaceIBO;
        BufferLayoutObject layout;

    public:
        
        Surface(glm::vec3 color, Texture *t);
        VertexArray& GetVAO();
        IndexBuffer& GetIBO();
        std::string GetClassName() override;
        void Draw() override;

};