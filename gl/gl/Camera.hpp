#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "InputManager.hpp"

class Camera
{
public:
	Camera(InputManager* input);

	void update(double delta);
	glm::mat4 getView() const;
private:
	glm::vec3 pos;
	const GLfloat SPEED;
	GLfloat speedAdjusted;

	glm::vec3 front;
	double yaw;
	double pitch;

	const double MOUSE_SENSITIVITY = 0.5;

	glm::mat4 view;
};

#endif