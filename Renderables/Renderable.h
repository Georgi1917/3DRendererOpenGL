#pragma once
#define GLEW_STATIC
#include "../include/glew.h"
#include "../VertexArray.h"
#include "../VertexBuffer.h"
#include "../IndexBuffer.h"
#include "../BufferLayoutObject.h"
#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "../include/glm/gtc/type_ptr.hpp"

class Renderable
{

    protected:
        unsigned int id;
        glm::mat4 model;
        glm::vec3 color;
        glm::vec3 pickingColor;
        glm::vec3 IdToColor();
        unsigned int ColorToId(unsigned char r, unsigned char g, unsigned char b);

    public:

        Renderable(unsigned int _id, glm::vec3 _color);
        glm::vec3& GetColor();
        glm::vec3& GetPickingColor();
        bool CompareColorAndId(unsigned char r, unsigned char g, unsigned char b);

};