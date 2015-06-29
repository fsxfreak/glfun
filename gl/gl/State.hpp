#ifndef STATE_HPP
#define STATE_HPP

#include "Camera.hpp"
#include "InputManager.hpp"
#include "Primitive.hpp"

#include <memory>
#include <vector>

class State
{
public:
	State(InputManager* input);

	static const glm::vec3 UP;

	void constructScene();
	void drawScene(double delta);
private:
	std::vector<std::shared_ptr<Primitive>> primitives;

	Camera camera;
};

#endif