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
    Rectangle(const glm::vec3& p1
            , const glm::vec3& p2
            , const glm::vec3& p3
            , const glm::vec3& p4
            , const glm::vec3& rgb);
    Rectangle(const std::array<glm::vec3, NUM_VERTS>& pos, glm::vec3 rgb);
    ~Rectangle();

    virtual void draw(glm::mat4 view) const override;
    virtual void translate(const glm::vec3& amount) override;

private:
    std::array<GLuint, 6> indices;

    GLuint eboID;

    GLuint modelUniform;
    GLuint viewUniform;
    GLuint projectionUniform;
};

#endif