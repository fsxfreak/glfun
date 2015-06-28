#include "Camera.hpp"

#include "State.hpp"

Camera::Camera() : pos({ 0.0f, 0.0f, 3.0f }) {}

void Camera::update()
{
	pos.x = 3 * cos(glfwGetTime());
	pos.z = 3 * sin(glfwGetTime());

	glm::vec3 target = { 0.0f, 0.0f, 0.0f };
	glm::vec3 dir = glm::normalize(pos - target);

	glm::vec3 cameraRight = glm::normalize(glm::cross(State::UP, dir));
	glm::vec3 cameraUp = glm::cross(dir, cameraRight);

	view = glm::lookAt(pos, target, State::UP);
}

glm::mat4 Camera::getView() const { return view; }