#pragma once
#include "Renderable.h"

class Sphere : public Renderable
{

    private:
        unsigned int stacks, sectors;
        float radius;
        std::vector<float> vertices;
        std::vector<unsigned int> indices;

        VertexArray sphereVAO;
        VertexBuffer sphereVBO;
        IndexBuffer sphereIBO;
        BufferLayoutObject layout;
        void SetUpSphere();

    public:
        Sphere(glm::vec3 _color, float _radius, unsigned int _stacks, unsigned int _sectors);
        ~Sphere();
        VertexArray& GetVAO();
        IndexBuffer& GetIBO();
        std::string GetClassName() override;

};