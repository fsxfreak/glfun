#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
public:
	Camera();

	void update();
	glm::mat4 getView() const;
private:
	glm::vec3 pos;
	glm::mat4 view;
};

#endif