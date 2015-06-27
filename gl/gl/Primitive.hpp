#ifndef PRIMITIVE_HPP
#define PRIMITIVE_HPP

#include "Program.hpp"

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Primitive
{
public:
	Primitive();

	virtual void draw() = 0;
	virtual void setColor(glm::vec3 rgb, unsigned int index) = 0;
	virtual void setPosition(glm::vec3 pos, unsigned int index) = 0;
	virtual glm::vec3 getColor(unsigned int index) const = 0;
	virtual glm::vec3 getPosition(unsigned int index) const = 0;
	virtual void setProgram(const std::string& vertex, const std::string& fragment);
protected:
	GLuint vaoID;
	GLuint vboID;
	Program program;
};

#endif