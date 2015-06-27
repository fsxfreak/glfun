#ifndef PRIMITIVE_HPP
#define PRIMITIVE_HPP

#include "Program.hpp"

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Primitive
{
public:
	Primitive();

	virtual void draw() = 0;
	virtual void setProgram(const std::string& vertex, const std::string& fragment);
protected:
	GLuint vaoID;
	GLuint vboID;
	Program program;
};

#endif