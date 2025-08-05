#define GLEW_STATIC
#include "include/glew.h"
#include "Shader.h"
#include <fstream>
#include <sstream>

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

    return shader;

}

Shader::Shader(std::string &vertexFilePath, std::string &fragmentFilePath)
{

    unsigned int vertexShader, fragmentShader;
    int program;
    vertexShader = CompileShader(vertexFilePath, GL_VERTEX_SHADER);
    fragmentShader = CompileShader(fragmentFilePath, GL_FRAGMENT_SHADER);

    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    glUseProgram(program);

}

Shader::~Shader()
{

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

}

