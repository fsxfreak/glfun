#include "Camera.hpp"

#include "State.hpp"

Camera::Camera(InputManager *input) : pos({ 0.0f, 0.0f, 3.0f }), front({ 0.0f, 0.0f, -1.0f }), SPEED(1.5f) 
{
	input->bind(GLFW_KEY_W, 
		[&]() {
			pos += speedAdjusted * front;
		}
	);
	input->bind(GLFW_KEY_A,
		[&]() {
			pos -= speedAdjusted * glm::normalize(glm::cross(front, State::UP));
		}
	);
	input->bind(GLFW_KEY_S,
		[&]() {
			pos -= speedAdjusted * front;
		}
	);
	input->bind(GLFW_KEY_D,
		[&]() {
			pos += speedAdjusted * glm::normalize(glm::cross(front, State::UP));
		}
	);
}

void Camera::update(double delta)
{
	front.x = cos(glm::radians(0.0f)) * cos(glm::radians(4.0f));
	front.y = sin(glm::radians(0.0f));
	front.z = cos(glm::radians(0.0f)) * sin(glm::radians(4.0f));

	view = glm::lookAt(pos, pos + front, State::UP);
	speedAdjusted = SPEED * delta;
}

glm::mat4 Camera::getView() const { return view; }