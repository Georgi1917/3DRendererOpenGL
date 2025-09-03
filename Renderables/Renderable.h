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
#include "../Textures/Texture.h"
#include <string>

class Renderable
{

    protected:
        static unsigned int staticId;
        glm::vec3 lightColor;
        unsigned int id;
        glm::mat4 model;
        static glm::vec3 staticTranslation;
        glm::vec3 translation;
        glm::vec3 rotation;
        glm::vec3 scale;

        glm::vec3 color;
        glm::vec3 pickingColor;
        Texture *tex;
        glm::vec3 IdToColor();
        unsigned int ColorToId(unsigned char r, unsigned char g, unsigned char b);

    public:

        Renderable();
        Renderable(Texture *t);
        Renderable(glm::vec3 _color);
        Renderable(glm::vec3 _color, Texture *t);
        glm::vec3& GetColor();
        glm::vec3& GetPickingColor();
        bool CompareColorAndId(unsigned char r, unsigned char g, unsigned char b);
        glm::mat4& GetModelMatrix();
        virtual std::string GetClassName();
        virtual void Draw();
        void ResetModelMatrix();
        void SetTranslation(glm::vec3 worldRay);
        glm::vec3& GetTranslation();
        glm::vec3& GetRotation();
        glm::vec3& GetScale();
        glm::vec3& GetLightColor();
        Texture *GetTexture();
        void RemoveTexture();
        void SetTexture(Texture *t);
        

};