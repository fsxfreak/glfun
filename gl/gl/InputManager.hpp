#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <array>
#include <functional>
#include <map>

class InputManager
{
public:
	void keyPressed(GLFWwindow* window, int key, int scancode, int action, int mode);
	void mouseMoved(GLFWwindow* window, double xpos, double ypos);
	void bind(int key, std::function<void()> func);
	void update();
private:
	std::array<bool, 512> keyStates;
	std::map<int, std::function<void()>> callbacks;
};

#endif