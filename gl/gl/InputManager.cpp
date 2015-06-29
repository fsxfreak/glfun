#include "InputManager.hpp"

#include <algorithm>
#include <iostream>

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
	//starting condition, so camera doesn't snap somewhere random
	if (lastX == -1.0 || lastY == -1.0)
	{
		lastX = xpos;
		lastY = ypos;
	}

	diffX = xpos - lastX;
	diffY = lastY - ypos;

	lastX = xpos;
	lastY = ypos;
}

void InputManager::bind(int key, std::function<void()> keyFunc)
{
	keyCallbacks[key] = keyFunc;
}

void InputManager::bind(std::function<void(double, double)> mouseFunc)
{
	mouseCallback = mouseFunc;
}

void InputManager::update()
{
	/* Iterate through map, or iterate through array, which is better?
	 * I expect to have less than 512 callbacks registered, but is
	 * constructing a pair for each map element slower than searching
	 * through a constant 512 booleans?
	 * Will have to benchmark this in the future if performance becomes an issue.
	 */
	std::for_each(keyCallbacks.begin(), keyCallbacks.end()
		, [&] (const std::pair<int, std::function<void()>>& e) {
			if (keyStates[e.first])
			{
				e.second();
			}
		}
	);

	if (std::abs(diffX) > 0.33 || std::abs(diffY) > 0.33)
	{
		mouseCallback(diffX, diffY);
		diffX = diffY = 0;
	}
}