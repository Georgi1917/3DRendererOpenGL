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
        Sphere(unsigned int _id, float _radius, unsigned int _stacks, unsigned int _sectors);
        ~Sphere();

};