#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <memory>

#include "InputManager.hpp"
#include "State.hpp"

class Engine
{
public:
    static unsigned int width;
    static unsigned int height;

    Engine(int width, int height, InputManager *input);
    ~Engine();

    void setActiveState(std::shared_ptr<State> state);

    void loop();
private:
    //using raw ptr because glfwTerminate is responsible for destruction
    GLFWwindow *window;
    std::shared_ptr<State> activeState;

    InputManager *input;

    double lastTime;
};

#endif