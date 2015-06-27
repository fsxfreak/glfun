#ifndef STATE_HPP
#define STATE_HPP

#include "Primitive.hpp"

#include <memory>
#include <vector>

class State
{
public:
	State();

	void constructScene();
	void drawScene();
private:
	std::vector<std::shared_ptr<Primitive>> primitives;
};

#endif