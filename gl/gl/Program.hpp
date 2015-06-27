#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

/*
* Todo: programs do not know when they already have been linked somewhere else
*		Add support to cache linked programs for reuse.
*/
class Program
{
public:
	Program(const std::string& vertex = "test.vert", const std::string& fragment = "test.frag");

	void use() const;
	GLuint getID() const;
private:
	GLuint id;
};

#endif