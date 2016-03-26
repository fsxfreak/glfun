#include "Primitive.hpp"

Primitive::Primitive(unsigned int NUM_VERTS, unsigned int STRIDE, unsigned int SIZE) 
    : program(), NUM_VERTS(NUM_VERTS), STRIDE(STRIDE), SIZE(SIZE), vertData(SIZE)
{}

void Primitive::setProgram(const std::string& vertex, const std::string& fragment)
{
    program = Program(vertex, fragment);
}

void Primitive::transform(const glm::mat4& amount)
{
    modelTransform *= amount;
}

void Primitive::setColor(glm::vec3 rgb, unsigned int index)
{
    if (index >= NUM_VERTS) return;

    vertData[STRIDE * index + 3] = rgb.x;
    vertData[STRIDE * index + 4] = rgb.y;
    vertData[STRIDE * index + 5] = rgb.z;

    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferSubData(GL_ARRAY_BUFFER
        , sizeof(GLfloat) * (STRIDE * index + 3)
        , sizeof(GLfloat) * 3
        , &vertData[STRIDE * index + 3]);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

glm::vec3 Primitive::getColor(unsigned int index) const
{
    if (index >= NUM_VERTS) { return glm::vec3(); }

    return{
        vertData[index * STRIDE + 3],
        vertData[index * STRIDE + 4],
        vertData[index * STRIDE + 5]
    };
}

void Primitive::setPosition(glm::vec3 pos, unsigned int index)
{
    if (index >= NUM_VERTS) return;

    vertData[STRIDE * index] = pos.x;
    vertData[STRIDE * index + 1] = pos.y;
    vertData[STRIDE * index + 2] = pos.z;

    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferSubData(GL_ARRAY_BUFFER
        , sizeof(GLfloat) * (STRIDE * index + 0)
        , sizeof(GLfloat) * 3
        , &vertData[STRIDE * index + 0]
        );
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

glm::vec3 Primitive::getPosition(unsigned int index) const
{
    if (index >= NUM_VERTS) { return glm::vec3(); }

    return{
        vertData[index * STRIDE + 0],
        vertData[index * STRIDE + 1],
        vertData[index * STRIDE + 2]
    };
}