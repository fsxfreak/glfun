#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "Primitive.hpp"
#include "Program.hpp"

#include <array>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct Vector3
{
	GLfloat x;
	GLfloat y;
	GLfloat z;

	Vector3(GLfloat x, GLfloat y, GLfloat z) : x(x), y(y), z(z) {}
};

class Triangle : public Primitive
{
public:
	Triangle(const std::array<Vector3, 3>& pos, Vector3 rgb);
	Triangle(const std::array<Vector3, 3>& pos, const std::array<Vector3, 3>& rgb);

	virtual void draw();
};

#endif
