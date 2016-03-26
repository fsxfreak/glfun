#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "Primitive.hpp"
#include "Program.hpp"

#include <array>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Triangle : public Primitive
{
private:
    const static unsigned int NUM_VERTS = 3;
    const static unsigned int STRIDE = 6;
    const static unsigned int SIZE = NUM_VERTS * STRIDE;

public:
    Triangle(const std::array<glm::vec3, NUM_VERTS>& pos, glm::vec3 rgb);
    Triangle(const std::array<glm::vec3, NUM_VERTS>& pos, const std::array<glm::vec3, NUM_VERTS>& rgb);
    ~Triangle();

    virtual void draw(glm::mat4 view) const override;
    virtual void translate(const glm::vec3& amount) override;
private:
    GLuint modelUniform;
    GLuint viewUniform;
    GLuint projectionUniform;
};

#endif
