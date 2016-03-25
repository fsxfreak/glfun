#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "Primitive.hpp"
#include "Program.hpp"

#include <array>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Rectangle : public Primitive
{
private:
    const static unsigned int NUM_VERTS = 4;
    const static unsigned int STRIDE = 6;
    const static unsigned int SIZE = NUM_VERTS * STRIDE;

public:
    Rectangle(const std::array<glm::vec3, NUM_VERTS>& pos, glm::vec3 rgb);
    ~Rectangle();

    virtual void draw(glm::mat4 view) const;
    virtual void setColor(glm::vec3 rgb, unsigned int index);
    virtual void setPosition(glm::vec3 pos, unsigned int index);

    virtual glm::vec3 getColor(unsigned int index) const;
    virtual glm::vec3 getPosition(unsigned int index) const;

private:
    std::array<GLfloat, SIZE> vertData;

    GLuint eboID;

    GLuint modelUniform;
    GLuint viewUniform;
    GLuint projectionUniform;
};

#endif