#include "Camera.hpp"
#include "State.hpp"

#include <iostream>

Camera::Camera(InputManager *input) 
    : pos({ 3.0f, 3.0f, 3.0f }), SPEED(1.5f), speedAdjusted(0.0f)
    , front({ -1.0f, -1.0f, -1.0f }), yaw(0.0), pitch(0.0)
{
    front = glm::normalize(front);

    pitch = asin(front.y);
    yaw = std::atan2(front.z, front.x);

    pitch = glm::degrees(pitch);
    yaw = glm::degrees(yaw);

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

    input->bind(GLFW_KEY_Q,
        [&]() {
            pos -= speedAdjusted * State::UP;
        }
    );

    input->bind(GLFW_KEY_E,
        [&]() {
            pos += speedAdjusted * State::UP;
        }
    );

    input->bind([&](double yawAmount, double pitchAmount) {
            yawAmount *= MOUSE_SENSITIVITY;
            pitchAmount *= MOUSE_SENSITIVITY;

            yaw += yawAmount;
            pitch += pitchAmount;

            if (pitch > 89.0) pitch = 89.0;
            else if (pitch < -89.0) pitch = -89.0;
            
            front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
            front.y = sin(glm::radians(pitch));
            front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));

            front = glm::normalize(front);
        }
    );
}

void Camera::update(double delta)
{
    view = glm::lookAt(pos, pos + front, State::UP);
    speedAdjusted = SPEED * delta;
}

glm::mat4 Camera::getView() const { return view; }