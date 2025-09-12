#define GLEW_STATIC
#include "include/glew.h"
#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::string Shader::GetShaderSource(std::string &source)
{

    std::ifstream f(source);
    std::string line;
    std::stringstream out;

    while(std::getline(f, line))
        out << line << "\n";

    return out.str();

}

unsigned int Shader::CompileShader(std::string &filepath, unsigned int type)
{

    std::string source = GetShaderSource(filepath);
    unsigned int shader;
    shader = glCreateShader(type);
    const char *src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    char infoLog[512];
    int success;

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        std::cout << infoLog << "\n";
    }

    return shader;

}

Shader::Shader(std::string vertexFilePath, std::string fragmentFilePath)
{

    unsigned int vertexShader, fragmentShader;
    int program;
    vertexShader = CompileShader(vertexFilePath, GL_VERTEX_SHADER);
    fragmentShader = CompileShader(fragmentFilePath, GL_FRAGMENT_SHADER);

    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    shaderProgram = program;

    glUseProgram(program);

}

Shader::~Shader()
{

    glDeleteProgram(shaderProgram);

}

void Shader::Bind()
{

    glUseProgram(shaderProgram);

}

void Shader::Unbind()
{

    glUseProgram(0);

}

void Shader::SetMatrix4fv(std::string uniformName, glm::mat4 &matrix)
{

    int loc = glGetUniformLocation(shaderProgram, uniformName.c_str());
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));

}

void Shader::SetVec3f(std::string uniformName, glm::vec3 &vector3)
{

    int loc = glGetUniformLocation(shaderProgram, uniformName.c_str());

    //if (loc < 0) std::cout << "Not Found" << "\n";

    glUniform3f(loc, vector3.r, vector3.g, vector3.b);

}

void Shader::SetBool(std::string uniformName, bool b)
{

    int loc = glGetUniformLocation(shaderProgram, uniformName.c_str());

    glUniform1i(loc, b);

}

void Shader::Set1I(std::string uniformName, int i)
{

    int loc = glGetUniformLocation(shaderProgram, uniformName.c_str());
    glUniform1i(loc, i);

}

int Shader::GetProgram()
{
    return shaderProgram;
}