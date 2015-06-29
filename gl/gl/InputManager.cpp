#include "InputManager.hpp"

#include <algorithm>

void InputManager::keyPressed(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	switch (action)
	{
	case GLFW_PRESS: case GLFW_REPEAT:
		keyStates[key] = true;
		break;
	case GLFW_RELEASE:
		keyStates[key] = false;
		break;
	}
}

void InputManager::mouseMoved(GLFWwindow* window, double xpos, double ypos)
{

}

void InputManager::bind(int key, std::function<void()> func)
{
	callbacks[key] = func;
}

void InputManager::update()
{
	/* Iterate through map, or iterate through array, which is better?
	 * I expect to have less than 512 callbacks registered, but is
	 * constructing a pair for each map element slower than searching
	 * through a constant 512 booleans?
	 * Will have to benchmark this in the future if performance becomes an issue.
	 */
	std::for_each(callbacks.begin(), callbacks.end()
		, [&] (const std::pair<int, std::function<void()>>& e) {
			if (keyStates[e.first])
			{
				e.second();
			}
		}
	);
}