#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <array>
#include <functional>
#include <map>
#include <string>

class InputManager
{
public:
	void keyPressed(GLFWwindow* window, int key, int scancode, int action, int mode);
	void bind(int key, std::function<void()> keyFunc);

	void mouseMoved(GLFWwindow* window, double xpos, double ypos);
	void bind(std::function<void(double, double)> mouseFunc);

	void update();
private:
	std::array<bool, 512> keyStates;
	std::map<int, std::function<void()>> keyCallbacks;
	
	double lastX = -1.0;
	double lastY = -1.0;
	double diffX;
	double diffY;
	std::function<void(double, double)> mouseCallback;
};

#endif