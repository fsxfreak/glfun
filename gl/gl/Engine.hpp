#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <memory>

#include "State.hpp"

class Engine
{
public:
	Engine(int width, int height);
	~Engine();

	void setActiveState(std::shared_ptr<State> state);

	void loop();

	void keyPressed(GLFWwindow* window, int key, int scancode, int action, int mode);
private:
	//using raw ptr because glfwTerminate is responsible for destruction
	GLFWwindow *window;
	std::shared_ptr<State> activeState;
};

#endif