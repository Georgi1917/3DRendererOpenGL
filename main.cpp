#define GLEW_STATIC
#include "include/glew.h"
#include "include/glfw3.h"
#include "include/glm/glm.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include "include/glm/gtc/type_ptr.hpp"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

std::string GetShaderSources(std::string &source)
{

    std::ifstream f(source);
    std::string line;
    std::stringstream out;

    while(std::getline(f, line))
        out << line << "\n";

    std::cout << out.str() << "\n";

    return out.str();

}

int CreateProgram(std::string &vs, std::string &fs)
{

    unsigned int vertex, fragment;
    int program;
    vertex = glCreateShader(GL_VERTEX_SHADER);
    fragment = glCreateShader(GL_FRAGMENT_SHADER);

    const char *vsrc = vs.c_str();
    const char *fsrc = fs.c_str();

    glShaderSource(vertex, 1, &vsrc, nullptr);
    glShaderSource(fragment, 1, &fsrc, nullptr);

    glCompileShader(vertex);
    glCompileShader(fragment);

    program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return program;

}

int main()
{

    GLFWwindow *window;

    if (!glfwInit())
    {
        return -1;
    }

    window = glfwCreateWindow(1280, 720, "Renderer", NULL, NULL);

    if(!window)
    {
        return -1;
    }

    glfwMakeContextCurrent(window);
    glewInit();

    float positions[] = {
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
        0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
        0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,

        0.5f,  0.5f,  0.5f,  0.29f, 0.6f, 0.57f,
        0.5f,  0.5f, -0.5f,  0.29f, 0.6f, 0.57f,
        0.5f, -0.5f, -0.5f,  0.29f, 0.6f, 0.57f,
        0.5f, -0.5f, -0.5f,  0.29f, 0.6f, 0.57f,
        0.5f, -0.5f,  0.5f,  0.29f, 0.6f, 0.57f,
        0.5f,  0.5f,  0.5f,  0.29f, 0.6f, 0.57f,

        -0.5f, -0.5f, -0.5f, 1.0f, 0.6f, 0.12f, 
        0.5f, -0.5f, -0.5f,  1.0f, 0.6f, 0.12f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.6f, 0.12f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.6f, 0.12f,
        -0.5f, -0.5f,  0.5f, 1.0f, 0.6f, 0.12f,
        -0.5f, -0.5f, -0.5f, 1.0f, 0.6f, 0.12f,

        -0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 
        -0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 1.0f
    };

    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f), 
        glm::vec3( 2.0f,  5.0f, -15.0f), 
        glm::vec3(-1.5f, -2.2f, -2.5f),  
        glm::vec3(-3.8f, -2.0f, -12.3f),  
        glm::vec3( 2.4f, -0.4f, -3.5f),  
        glm::vec3(-1.7f,  3.0f, -7.5f),  
        glm::vec3( 1.3f, -2.0f, -2.5f),  
        glm::vec3( 1.5f,  2.0f, -2.5f), 
        glm::vec3( 1.5f,  0.2f, -1.5f), 
        glm::vec3(-1.3f,  1.0f, -1.5f)  
    };

    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    std::string vs = "shaders/vertex.shader";
    std::string fs = "shaders/fragment.shader";

    std::string vsSource = GetShaderSources(vs);
    std::string fsSource = GetShaderSources(fs);

    int program = CreateProgram(vsSource, fsSource);

    glUseProgram(program);

    glm::mat4 models = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection;

    const float radius = 10.0f;

    projection = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 1.0f, 100.0f);

    int vLoc = glGetUniformLocation(program, "view");
    int pLoc = glGetUniformLocation(program, "projection");
    glUniformMatrix4fv(pLoc, 1, GL_FALSE, glm::value_ptr(projection));

    glEnable(GL_DEPTH_TEST);

    while(!glfwWindowShouldClose(window))
    {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float camX = sin(glfwGetTime()) * radius;
        float camZ = cos(glfwGetTime()) * radius;

        view = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(vLoc, 1, GL_FALSE, glm::value_ptr(view));

        for (unsigned int i = 0; i < 10; i++)
        {

            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            int mLoc = glGetUniformLocation(program, "model");
            glUniformMatrix4fv(mLoc, 1, GL_FALSE, glm::value_ptr(model));

            glDrawArrays(GL_TRIANGLES, 0, 36);

        }

        glfwSwapBuffers(window);

        glfwPollEvents();

    }

    glfwTerminate();
    return 0;

}