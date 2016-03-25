#include "State.hpp"
#include "Triangle.hpp"
#include "Rectangle.hpp"

#include <cmath>
#include <iostream>

const glm::vec3 State::UP = glm::vec3(0.0f, 1.0f, 0.0f);

State::State(InputManager* input) : camera(input)
{
    constructScene();
}

void State::constructScene()
{
    using glm::vec3;
    vec3 color = { 1.0f, 1.0f, 1.0f };
    
    std::array<vec3, 3> triVerts = { vec3{-2.0f, 0.0f, 1.0f}, vec3{-2.0f, 0.0f, -1.0f}, vec3{-1.0f, 0.0f, 1.0f} };    
    std::shared_ptr<Triangle> tri = std::make_shared<Triangle>(triVerts, color);
    primitives.push_back(tri);

    triVerts = { vec3{-1.0f, 0.0f, -1.0f}, vec3{1.0f, 0.0f, -1.0f}, vec3{1.0f, 0.0f, 1.0f} };
    tri = std::make_shared<Triangle>(triVerts, color);
    primitives.push_back(tri);
    
    std::array<vec3, 4> rectVerts = {
        vec3{-1.0f, 0.5f, 1.0f}
      , vec3{1.0f, 0.5f, 1.0f}
      , vec3{1.0f, 0.5f, -1.0f}
      , vec3{-1.0f, 0.5f, -1.0f}
    };
    std::shared_ptr<Rectangle> rect = std::make_shared<Rectangle>(rectVerts, color);
    
    primitives.push_back(rect);
}

void State::drawScene(double delta)
{
    camera.update(delta);

    for (auto &e : primitives)
    {
        GLfloat blue = static_cast<float>(sin(glfwGetTime() + 3.1415f / 2)) / 2 + 0.5f;
        GLfloat green = static_cast<float>(sin(glfwGetTime())) / 2 + 0.5f;
        GLfloat red = static_cast<float>(sin(glfwGetTime() - 3.1415f / 2)) / 2 + 0.5f;
        e->setColor({ 0.1f, 0.2f, blue }, 0);
        e->setColor({ 0.2f, green, 0.1f }, 1);
        e->setColor({ red, 0.1f, 0.2f }, 2);
        e->setColor({ red * green, green * blue, blue * red }, 3);

        e->draw(camera.getView());
    }
}