#include "State.hpp"
#include "Triangle.hpp"

#include <cmath>

const glm::vec3 State::UP = glm::vec3(0.0f, 1.0f, 0.0f);

State::State()
{
	constructScene();
}

void State::constructScene()
{
	std::shared_ptr<Triangle> tri = std::make_shared<Triangle>(Triangle(
		{
			{ glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f) }
			, { 0.0f, 0.0f, 0.0f }
		})
	);
	primitives.push_back(tri);
	tri = std::make_shared<Triangle>(Triangle(
		{
			{ glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec3(1.0f, -1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f) }
			, { 0.0f, 0.0f, 0.0f }
		})
	);
	primitives.push_back(tri);
}

void State::drawScene()
{
	camera.update();

	for (auto &e : primitives)
	{
		GLfloat blue = static_cast<float>(sin(glfwGetTime() + 3.1415f / 2)) / 2 + 0.5f;
		GLfloat green = static_cast<float>(sin(glfwGetTime())) / 2 + 0.5f;
		GLfloat red = static_cast<float>(sin(glfwGetTime() - 3.1415f / 2)) / 2 + 0.5f;
		e->setColor({ blue, 0.0f, 0.0f }, 0);
		e->setColor({ green, 0.0f, 0.0f }, 1);
		e->setColor({ red, 0.0f, 0.0f }, 2);

		e->draw(camera.getView());
	}
}