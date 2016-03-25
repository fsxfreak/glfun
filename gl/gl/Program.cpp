#include "Program.hpp"
#include "Program.hpp"
#include "Shader.hpp"

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

Program::Program(const std::string& vertex, const std::string& fragment)
{
    Shader vert = { vertex, GL_VERTEX_SHADER };
    Shader frag = { fragment, GL_FRAGMENT_SHADER };

    id = glCreateProgram();
    glAttachShader(id, vert.getID());
    glAttachShader(id, frag.getID());
    glLinkProgram(id);

    int success;
    char infoLog[512];
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(id, 512, nullptr, infoLog);
        std::cout << infoLog << std::endl;
    }
}

Program::~Program()
{
    glDeleteProgram(id);
}

void Program::use() const
{
    glUseProgram(id);
}

GLuint Program::getID() const
{
    return id;
}