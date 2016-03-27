#include "Engine.hpp"

#include <iostream>

unsigned int Engine::width = 800;
unsigned int Engine::height = 600;

Engine::Engine(int width, int height, InputManager *input) : input(input)
{
    Engine::width = width;
    Engine::height = height;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(width, height, "demo", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window." << std::endl;
        glfwTerminate();
        exit(-1);
    }

    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW." << std::endl;
        exit(-1);
    }

    glViewport(0, 0, width, height);

    glEnable(GL_DEPTH_TEST);

    glfwSetWindowUserPointer(window, input);

    auto keyCallback = [] (GLFWwindow* window, int key, int scancode, int action, int mode) {
        static_cast<InputManager*>(glfwGetWindowUserPointer(window))->keyPressed(
            window, key, scancode, action, mode);
    };
    glfwSetKeyCallback(window, keyCallback);
    auto mouseCallback = [] (GLFWwindow* window, double xpos, double ypos) {
        static_cast<InputManager*>(glfwGetWindowUserPointer(window))->mouseMoved(
            window, xpos, ypos);
    };
    glfwSetCursorPosCallback(window, mouseCallback);

    auto close = [&]() { glfwSetWindowShouldClose(window, GL_TRUE); };
    input->bind(GLFW_KEY_ESCAPE, close);
}

Engine::~Engine()
{
    glfwTerminate();
}

void Engine::setActiveState(std::shared_ptr<State> other)
{
    activeState = other;
}

void Engine::loop()
{
    while (!glfwWindowShouldClose(window))
    {
        double timeNow = glfwGetTime();
        double delta = timeNow - lastTime;
        lastTime = timeNow;

        glfwPollEvents();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        input->update();
        activeState->drawScene(delta);

        glfwSwapBuffers(window);
    }
}