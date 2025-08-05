#pragma once

#include <string>
#include "include/glm/glm.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include "include/glm/gtc/type_ptr.hpp"

class Shader
{

    private:
        unsigned int vertexShader;
        unsigned int fragmentShader;
        std::string GetShaderSource(std::string &source);
        unsigned int CompileShader(std::string &filepath, unsigned int type);

    public:
        Shader(std::string &vertexFilePath, std::string &fragmentFilePath);
        ~Shader();

        void Bind();
        void Unbind();

        void SetMatrix4fv(std::string &uniformName, glm::mat4 &matrix);

};