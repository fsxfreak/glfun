#ifndef PRIMITIVE_HPP
#define PRIMITIVE_HPP

#include "Program.hpp"

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct Vector3
{
	GLfloat x;
	GLfloat y;
	GLfloat z;

	Vector3(GLfloat x, GLfloat y, GLfloat z) : x(x), y(y), z(z) {}
};

class Primitive
{
public:
	Primitive();

	virtual void draw() = 0;
	virtual void setColor(Vector3 rgb, unsigned int index) = 0;
	virtual void setPosition(Vector3 pos, unsigned int index) = 0;
	virtual Vector3 getColor(unsigned int index) const = 0;
	virtual Vector3 getPosition(unsigned int index) const = 0;
	virtual void setProgram(const std::string& vertex, const std::string& fragment);
protected:
	GLuint vaoID;
	GLuint vboID;
	Program program;
};

#endif