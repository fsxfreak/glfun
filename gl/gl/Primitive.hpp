#ifndef PRIMITIVE_HPP
#define PRIMITIVE_HPP

#include "Program.hpp"
#include "Entity.hpp"

#include <vector>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

class Primitive : public Entity
{
public:
    Primitive(unsigned int NUM_VERTS, unsigned int STRIDE, unsigned int SIZE);

    virtual void transform(const glm::mat4& amount) override;

    virtual void setColor(glm::vec3 rgb, unsigned int index = 0) override final;
    virtual glm::vec3 getColor(unsigned int index = 0) const override final;

    virtual void setPosition(glm::vec3 pos, unsigned int index = 0) override final;
    virtual glm::vec3 getPosition(unsigned int index = 0) const override final;

    virtual void setProgram(const std::string& vertex, const std::string& fragment);
protected:
    const unsigned int NUM_VERTS;
    const unsigned int STRIDE;
    const unsigned int SIZE;

    GLuint vaoID;
    GLuint vboID;
    Program program;

    std::vector<GLfloat> vertData;

    glm::mat4 modelTransform;
};

#endif