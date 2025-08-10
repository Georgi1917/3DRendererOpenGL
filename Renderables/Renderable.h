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

    public:

        Renderable(unsigned int _id);

};