#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

/*
 * Todo: shaders do not know when they already have been compiled
 *		 Add support to cache shaders that have already been compiled
 */
class Shader
{
public:
	Shader(const std::string& shaderFile, GLenum type);
	~Shader();

	GLuint getID() const;
private:
	GLuint id;
};

#endif