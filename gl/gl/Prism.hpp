#ifndef PRISM_HPP
#define PRISM_HPP

#include "Primitive.hpp"
#include "Program.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Prism : public Primitive
{
public:
    static const unsigned int NUM_VERTS = 6;
    static const unsigned int STRIDE = 6;
    static const unsigned int SIZE = STRIDE * NUM_VERTS;

    Prism(const glm::vec3& centerBase
       , const unsigned int sideLength
       , const unsigned int height
       , const glm::vec3& color);
private:
};

#endif