#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <memory>

#include "Engine.hpp"
#include "Triangle.hpp"

int main()
{
	Engine engine(800, 600);
	std::shared_ptr<State> state = std::make_shared<State>();
	engine.setActiveState(state);
	engine.loop();

	glfwTerminate();
	return 0;
}