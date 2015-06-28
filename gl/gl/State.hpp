#ifndef STATE_HPP
#define STATE_HPP

#include "Camera.hpp"
#include "Primitive.hpp"

#include <memory>
#include <vector>

class State
{
public:
	State();

	static const glm::vec3 UP;

	void constructScene();
	void drawScene();
private:
	std::vector<std::shared_ptr<Primitive>> primitives;

	Camera camera;
};

#endif