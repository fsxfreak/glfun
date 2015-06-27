#include "State.hpp"

#include "Triangle.hpp"

State::State()
{
	constructScene();
}

void State::constructScene()
{
	std::shared_ptr<Triangle> tri = std::make_shared<Triangle>(Triangle(
			{
				{ Vector3(-1.0f, 1.0f, 0.0f), Vector3(-1.0f, -1.0f, 0.0f), Vector3(1.0f, 1.0f, 0.0f) }
				, { 1.0f, 1.0f, 0.0f }
			})
		);
	primitives.push_back(tri);
}

void State::drawScene()
{
	for (auto &e : primitives)
	{
		e->draw();
	}
}