#include "State.hpp"
#include "Triangle.hpp"

#include <cmath>

State::State()
{
	constructScene();
}

void State::constructScene()
{
	std::shared_ptr<Triangle> tri = std::make_shared<Triangle>(Triangle(
			{
				{ Vector3(-1.0f, 1.0f, 0.0f), Vector3(-1.0f, -1.0f, 0.0f), Vector3(1.0f, 1.0f, 0.0f) }
				, { 0.0f, 0.0f, 0.0f }
			})
		);
	primitives.push_back(tri);
}

void State::drawScene()
{
	for (auto &e : primitives)
	{
		GLfloat blue = static_cast<float>(sin(glfwGetTime() + 3.1415f)) / 2 + 0.5f;
		GLfloat green = static_cast<float>(sin(glfwGetTime() + 3.1415f / 2)) / 2 + 0.5f;
		GLfloat red = static_cast<float>(sin(glfwGetTime())) / 2 + 0.5f;
		e->setColor({ 0.0f, 0.0f, blue }, 0);
		e->setColor({ 0.0f, green, 0.0f }, 1);
		e->setColor({ red, 0.0f, 0.0f }, 2);
		e->draw();
	}
}