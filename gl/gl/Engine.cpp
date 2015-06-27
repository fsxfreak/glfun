#include "Engine.hpp"

#include <iostream>

Engine::Engine(int width, int height)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(width, height, "glfw window", nullptr, nullptr);
	if (!window)
	{
		std::cerr << "Failed to create GLFW window." << std::endl;
		glfwTerminate();
		exit(-1);
	}

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Failed to initialize GLEW." << std::endl;
		exit(-1);
	}

	glViewport(0, 0, width, height);

	glfwSetWindowUserPointer(window, this);
	auto callback = [] (GLFWwindow* window, int key, int scancode, int action, int mode) {
		static_cast<Engine*>(glfwGetWindowUserPointer(window))->keyPressed(
			window, key, scancode, action, mode);
	};
	glfwSetKeyCallback(window, callback);
}

Engine::~Engine()
{
	glfwTerminate();
}

void Engine::keyPressed(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void Engine::setActiveState(std::shared_ptr<State> other)
{
	activeState = other;
}

void Engine::loop()
{
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		activeState->drawScene();

		glfwSwapBuffers(window);
	}
}