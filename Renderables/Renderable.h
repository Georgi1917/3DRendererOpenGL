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
#include <string>

class Renderable
{

    protected:
        static unsigned int staticId;
        unsigned int id;
        glm::mat4 model;
        static glm::vec3 staticTranslation;
        glm::vec3 translation;
        glm::vec3 rotation;
        glm::vec3 scale;

        glm::vec3 color;
        glm::vec3 pickingColor;
        glm::vec3 IdToColor();
        unsigned int ColorToId(unsigned char r, unsigned char g, unsigned char b);

    public:

        Renderable(glm::vec3 _color);
        glm::vec3& GetColor();
        glm::vec3& GetPickingColor();
        bool CompareColorAndId(unsigned char r, unsigned char g, unsigned char b);
        glm::mat4& GetModelMatrix();
        virtual std::string GetClassName();
        void ResetModelMatrix();
        glm::vec3& GetTranslation();
        glm::vec3& GetRotation();
        glm::vec3& GetScale();

};