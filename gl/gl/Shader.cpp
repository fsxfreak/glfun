#include "Shader.hpp"

#include <iostream>
#include <fstream>

std::string getShaderFile(const std::string& name)
{
	const std::string SHADER_PATH = "../shaders/";
	std::ifstream shader(SHADER_PATH + name);
	if (!shader.is_open())
	{
		std::cerr << "Shader with " << name << " not found." << std::endl;
		return "";
	}
	std::string file;
	file.assign(std::istreambuf_iterator<char>(shader),
		std::istreambuf_iterator<char>());

	return file;
}

Shader::Shader(const std::string& shaderFile, GLenum type)
{
	std::string shaderCode = getShaderFile(shaderFile);
	id = glCreateShader(type);
	auto cstr = shaderCode.c_str();
	glShaderSource(id, 1, &cstr, nullptr);
	glCompileShader(id);

	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(id, 512, nullptr, infoLog);
		std::cerr << infoLog << std::endl;
	}
}

Shader::~Shader()
{
	glDeleteShader(id);
}

GLuint Shader::getID() const
{
	return id;
}